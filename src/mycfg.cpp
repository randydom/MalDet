#include"mycfg.hpp"
#include"myGlobal.h"


namespace myWPDS
{

///entry point
entryPoint* addEntryPoint(entryPoint* s,long v)
{
    entryPoint* t = (entryPoint*)malloc(sizeof(struct entryPoint));
    t->e = v;
    t->next = NULL;
    if(s == NULL)
        s = t;
    else
    {
        entryPoint* i =s;
        while(i->next!=NULL) i = i->next;
        i->next= t;
    }
    return s;
}

/// node
node* createNode(char*inst,int r1, int v1, int r2, int v2)
{
    node* ret = (node*)malloc(sizeof(struct node));

    ret->inst =duplicate(inst);
    ret->r1=r1;
    ret->r2=r2;
    ret->v1=v1;
    ret->v2=v2;
    ret->next1=-1;
    ret->next2=-1;
    ret->api=false;
    return ret;
}

/// CFG construction
node* getValue(std::map<long, boost::any> m, long v)
{

    std::map<long, boost::any>::iterator it = m.find(v);
    node* ret=NULL;
    if(it != m.end())
    {
        ret = boost::any_cast<node*>(it->second);
    }
    return ret;
}

bool contain(std::set<std::string> m, std::string v)
{
    std::set<std::string>::iterator it;
    it = m.find(v);
    if(it!=m.end())
        return true;
    return false;
}

long checkOperand(int typ, long v)
{
    if(typ==2 ||
            (typ>=5 && typ<=7))
        return v;
    return -1;
}


int getOp(std::string s, long v, int typ)
{

    int id;
    /*the value of op is in the data segment.
        If type != 2, op can be a register, Memory Ref, Memory Reg*/
    if(typ==2)
            s = decimalToHex(v);

    if(typ==0)
        return 0;
        id = hashCode(s);
        nameDomain[id] = s; //name and value are stored in nameDomain
        return id;
}

std::map<long, boost::any> readNode(char* fname,entryPoint** start)
{
    //std::cout << "\tReading cfg nodes...\n";

    ///temporary use varSet to verify the structure while it is stored with node
    //std::map<long, boost::any> varSet;
    ///

    std::map<long, boost::any> m;
    std::fstream infile;
    infile.open(fname, std::fstream::in);
    //std::cout<< fname <<"\n";
    //assert(infile);
    if(infile==NULL)
    {
        std::cout << "File not found!\n";
    }


    ///handle multi entry points
    long t;
    infile >> t;
    //std::cout << t<<"\n";
    while(t>0 && infile!=NULL)
    {
        int v ;
        infile >> v;
        //std::cout << v<<"\n";
        *start=addEntryPoint(*start, v);
        t--;
    }


    //std::cout << "Line1" << line <<"\n";
    std::string line;
    std::getline(infile, line); //
    //std::cout << "Line1" << line <<"\n";// skip comment line
    std::getline(infile, line); //
    //std::cout << "Line1" << line <<"\n";// skip comment line

    while (std::getline(infile, line))
    {
        long addr;
        char *inst;
        int op1;
        int op2;
        long v1,v2;
        int typ1,typ2;
        //line = removeSpaces(line);
        //reading value
        std::vector<std::string> sp = split(line,"\t");

        addr = atol(sp.at(0).c_str());

        inst = duplicate(sp.at(1).c_str());

        //op1 = duplicate(sp.at(2).c_str());
        typ1 = atoi(sp.at(3).c_str());
        v1 = atol(sp.at(4).c_str());

        op1 = getOp(sp.at(2),v1,typ1); //name and value are stored in nameDomain

        //op2 = duplicate(sp.at(5).c_str());
        typ2 = atoi(sp.at(6).c_str());
        v2 = atol(sp.at(7).c_str());

        op2 = getOp(sp.at(5),v2,typ2); //name and value are stored in nameDomain

        //end reading

        node* t2 = createNode(inst, op1,v1, op2, v2);

        ///checking API calls
        if(strcmp(inst,"jmp")==0 || strcmp(inst,"call")==0 )
        {
            std::string s = boost::any_cast<std::string>(nameDomain[op1]);
            if((!boost::starts_with(s, "sub_")&&
                    !boost::starts_with(s, "loc_")))
            {
                t2->api=true;
            }
            else
            {
                std::vector<std::string> sp1 = split(s, "_");
                t2->v1 = hexToDecimal(sp1.at(1).c_str());
            }
        }

        m[addr] = t2;
    }
    infile.close();
    return m;
}

std::string getState(long addr, std::string op)
{

    std::map<std::string, std::set<std::string>> meanv = mStates[addr];
    std::set<std::string> v = meanv[op];

    if(v.size()<1)
    {
        return "-1";
    }
    std::cout << addr <<"\t"<< op;
     std::cout <<"\t" << *v.begin() <<"\n";
    return *v.begin();
}


std::map<long, boost::any> readEdge( std::map<long, boost::any> m,char* fname)
{
    //std::cout << "\tReading cfg edges...\n";
    std::fstream infile;
    infile.open(fname, std::fstream::in);
    if(infile==NULL)
        std::cout << "File not found!\n";
    //assert(infile);
    ///handle multi entry points
    long t;
    infile >> t;
    while(t>0 && infile!=NULL)
    {
        int v ;
        infile >> v;

        t--;
    }


    std::string line;
    std::getline(infile, line);
    //std::cout << "Line1" << line <<"\n";

    std::getline(infile, line);
    //std::cout << "Line1" << line <<"\n";

    long preAddr=-1;
    while (std::getline(infile, line))
    {
        long addr;
        char *inst;
        char *op1;
        char *op2;
        long v1,v2;
        int typ1,typ2;
        line = removeSpaces(line);
        //
        std::vector<std::string> sp = split(line,"\t");

        addr = atol(sp.at(0).c_str());

        inst = duplicate(sp.at(1).c_str());

        op1 = duplicate(sp.at(2).c_str());
        typ1 = atoi(sp.at(3).c_str());
        v1 = atol(sp.at(4).c_str());
        if(v1==-1)
            v1= atol(getState(addr,op1).c_str());


        op2 = duplicate(sp.at(5).c_str());
        typ2 = atoi(sp.at(6).c_str());
        v2 = atol(sp.at(7).c_str());
        if(v2==-1)
            v2= atol(getState(addr,op2).c_str());


        if(preAddr>0)
        {
            node* preN = boost::any_cast<node*>(m[preAddr]);
            if(preN->next1<1)
            {
                preN->next1 = addr;
            }
            else if(preN->next2<1)
            {
                preN->next2=addr;
            }

            else
                std::cout<<"2 branches at "<<preAddr << "\n";
            m[preAddr] = preN; //update node when update the links

            std::map<long, boost::any>::iterator it= m.find(addr);
            if(it!=m.end())
            {
                node* n1 = boost::any_cast<node*>(it->second);
                n1->reached = true;
                m[addr]=n1;
            }
        }

        node* n = boost::any_cast<node*>(m[addr]);

        /*move to the jump address*/
        if(strcmp(inst,"jmp")==0)
        {

            if(v1==-1)
            {
                char *cstr = getAddr(op1);
                if(cstr!=NULL)
                {
                    v1 = hexToDecimal(cstr);
                }
            }

            //move to the jump address
            n->next1 = v1;


            std::map<long, boost::any>::iterator it= m.find(v1);
            if(it!=m.end())
            {
                node* n1 = boost::any_cast<node*>(it->second);
                n1->reached = true;
                m[v1]=n1;
            }


            preAddr=-1;

        }
        else
        {
            /*otherwise, move to the next address*/
            preAddr = addr; //store the current addr for updating the link in the next iteration

            /*stop moving if return*/
            if(strcmp(inst, "retn")==0 || strcmp(inst, "ret")==0
                    || strcmp(inst, "retf")==0)
            {
                preAddr = addr;
                //preAddr = -1; //if be a return statement, stop (no link)
            }

            /*move to jump address and to the next address if be a conditional jump*/
            if (boost::starts_with(inst, "j"))
            {
                //std::cout << addr << " "<< inst <<" "<<op1<<"\n";
                if(v1==-1)
                {

                    char *cstr = getAddr(op1);
                    if(cstr!=NULL)
                    {
                        v1 = hexToDecimal(cstr);
                    }
                }

                n->next1 = v1; //move to the jump address

                std::map<long, boost::any>::iterator it= m.find(v1);
                if(it!=m.end())
                {
                    node* n1 = boost::any_cast<node*>(it->second);
                    n1->reached = true;
                    m[v1]=n1;
                }
            }
        }

    }
    infile.close();
    return m;
}


void print_nameDomain(std::string filename)
{
    std::fstream outfile;
    std::string line;

    outfile.open(filename, std::fstream::out);
    assert(outfile);

    //std::cout << nameDomain.size()<<"\n";

    outfile <<nameDomain.size()<<"\n";

    std::map<int, std::string>::iterator it = nameDomain.begin();
    while(it!=nameDomain.end())
    {
        //std::string s = boost::any_cast<std::string>(nameDomain[it->first]);
        //std::cout << it->first << "\t" <<s <<"\t" << it->second  <<"\n";
        //std::cout << it->first << "\t" << it->second  <<"\n";
        outfile << it->first << "\t" << it->second  <<"\n";
        it++;
    }

    outfile.close();
}

std::map<int, std::string> NAMEDOMAIN(){
    return nameDomain;
}


std::map<long, boost::any> createCFG(char* fname, entryPoint** start)
{
    //std::cout << "Create CFG...\n";
    std::map<long, boost::any> m = readNode(fname,start);
    readEdge(m,fname);

    /*compute the entry points*/
    int count=0;
    for(std::map<long, boost::any>::iterator it = m.begin();it!=m.end();it++)
    {
        long addr = it->first;
        node* n = boost::any_cast<node*>(it->second);
        if(!n->reached)
        {
            count++;
            entryPoint* i = *start;
            while(i->next!=NULL)
            {
                if(i->e==addr)
                    break;
                i = i->next;
            }
            if(i->next==NULL && i->e!=addr)
            {
                entryPoint* ni = new entryPoint;
                ni->e = addr;
                ni->next = NULL;
                i->next = ni;
            }
        }
    }
    //std::cout <<"\t\t unreachable "<< count <<"\n";
    /**/
    return m;
}


}


