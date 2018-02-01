#include <boost/any.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
//#include <boost/filesystem.hpp>
//#include <boost/filesystem/operations.hpp>   // includes path.hpp
//#include <boost/filesystem/convenience.hpp>

#include <map>
#include <set>
#include <string>
#include <stack>
#include <thread>
#include <mutex>



#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>
#include <stdio.h>
#include <stdlib.h>

#include"myUtil.hpp"
#include "myWPDS.hpp"
#include"mycfg.hpp"

using namespace std;

//using namespace capi;

namespace myWPDS
{

/**
Check valid address in mCFG
**/
node* isValid(long addr)
{
    if(mCFG.find(addr)==mCFG.end())
        return NULL;
    node* t =NULL;
    try
    {
        t = boost::any_cast<node*>(mCFG[addr]);
    }
    catch(exception& e)
    {
        throw e;
    }
    return t;

}

template <typename T>
T getValue(std::string v, std::map<std::string,T> &m)
{
    T t=NULL;
    if(m.find(v)==m.end())
        return t;

    try
    {
        t = boost::any_cast<T>(m[v]);
    }
    catch(exception& e)
    {
        throw e;
    }
    return t;
}


/**
Check is number
**/
bool isNumber(std::string s)
{
 bool is_a_number = false;
    try
    {
        boost::lexical_cast<long>(s);
        is_a_number = true;
    }
    catch(boost::bad_lexical_cast &)
    {
        // if it throws, it's not a number.
    }
    return is_a_number;
}


void readJakstabState(std::string filename)
{
    //std::cout << "\tRead States...\n";
    std::fstream infile;
    infile.open(filename+"_States.out", std::fstream::in);

    if(infile==NULL)
    {
        std::cout << "File not found\n";
    }

    std::string line;
    std::getline(infile, line);
   // std::cout << line << std::endl;
    std::getline(infile, line);
    //std::cout << line << std::endl;
    std::getline(infile, line);
    //std::cout << line << std::endl;
    std::getline(infile, line);
    //std::cout << line << std::endl;
    while(std::getline(infile, line))
    {
        if(line.length()<1)
            continue;
        line = removeChar(line, '(');
        line = removeChar(line, ')');
        line = removeChar(line, '$');

        std::vector<std::string> sp = split(line, "{");
        if(sp.size()<2)
            continue;
        line = sp.at(1);    //the second part
        sp = split(sp.at(0), "_");
        sp = split(sp.at(0), "x");
        if(sp.size()<2)
            continue;
        long addr = hexToDecimal(sp.at(1).c_str());

        sp = split(line, "}");
        if(sp.size()<2)
            continue;
        line = sp.at(0);    //the second part
        line = removeSpaces(line);
        sp = split(line, ",");

        //std::cout <<addr << std::endl;

        std::map<std::string, stringSet> meanv;

        meanv = mStates[addr];

        for(int i=0;i<sp.size();i++)
        {
            std::vector<std::string>  s1 = split(sp.at(i),"=");
            if(s1.size()<2)
                continue;
            if(!isNumber(s1.at(1)))
                continue;

            stringSet v = meanv[s1.at(0)];
            v.insert(s1.at(1));

            meanv[s1.at(0)]= v;
            //std::cout <<"\t" << s1.at(0) << ":"<< s1.at(1)<<std::endl;
        }
        mStates[addr] = meanv;
    }

    infile.close();

    /*
    std::map<long, std::map<std::string, stringSet>>::iterator it;
    for(it = mStates.begin();it !=mStates.end();it++)
    {
        long addr = it->first;
        std::cout << addr<<":";
        std::map<std::string, stringSet> meanv = mStates[addr];//boost::any_cast<std::map<std::string, stringSet>>(it->second);
        std::map<std::string, stringSet>::iterator it1;
        for(it1= meanv.begin();it1 !=meanv.end();it1++)
        {

            std::string name= it1->first;
            stringSet v = boost::any_cast<stringSet>(it1->second);

            std::cout  << name <<"=\{";

            stringSet::iterator it2;

            for(it2 = v.begin();it2!=v.end();it2++)
            {
                 std::cout << *it2 <<",";
            }
            std::cout <<"\}";
        }
        std::cout <<std::endl;
    }*/
}


std::string createRule(long addr,std::string sym0,long next, std::string sym1,std::string sym2, int i0,int i1)
{
    return createRule(decimalToHex(addr),sym0,decimalToHex(next),sym1,sym2,i0,i1);

}

std::string createRule(std::string addr,std::string sym0,std::string next, std::string sym1,std::string sym2, int i0,int i1)
{

    /*Create a rule*/
    pdsRule* rule = new pdsRule;
    rule->n0 = addr;
    rule->n1 = next;
    rule->s0 = replace(sym0,"-","S");
    rule->s1 = replace(sym1,"-","S");
    rule->s2 = replace(sym2,"-","S");
    pdsRuleSet* ruleS  = getValue(addr, Lpds);
    if(ruleS==NULL)
        ruleS = new pdsRuleSet;
    ruleS->insert(rule);
    Lpds[addr] = ruleS;

    /*create a string rule for the output file*/
    std::string ret;

    std::string id0, id1;
    if(i0!=-1)
        id0 = "_"+ boost::lexical_cast<std::string>(i0);
    if(i1!=-1)
        id1 = "_"+ boost::lexical_cast<std::string>(i1);

    std::string s = sym2.length()==0?"":" ";
    std::string leftR = addr+id0 + " <"+sym0+">";
    std::string rightR;
    rightR = next+id1 +" <"+sym1+s+sym2+">";

    leftR = replace(leftR,"-","S");
    rightR = replace(rightR,"-","S");

    ret = leftR + " --> "+rightR;


    return ret;
}

std::string getTopStack(std::stack<std::string> stack_value)
{
    if(stack_value.empty())
        return "S1@S1";
    else
    {
        std::string ret(stack_value.top());
        return ret;
    }
}


/**
stack_value is computed by executing CFG
m is the CFG graph
addr is the current address
marked contains all configurations which are visited
**/
int traverse(std::stack<std::string> &stack_value, long addr,int depth, FILE* &f)
{
    /*reach the max depth of function call*/
    if(depth<0)
    {
        return 0;
    }


    /*invalid address*/
    if(addr<0 || mCFG.find(addr)==mCFG.end() )
    {
        return 0;
    }

    node* n = NULL;
    try
    {
        n = boost::any_cast<node*>(mCFG[addr]);
    }
    catch(const boost::bad_any_cast &)
    {
        std::cout << "traverse " << addr << "\n";
        return 0;
    }

    if(n==NULL)
        return 0;

    std::string saddr = boost::lexical_cast<std::string>(addr);
    std::string topStack = saddr +"@";
    topStack= topStack+getTopStack(stack_value);
    int hashTopStack = hashCode(topStack);
    if(marked.find(hashTopStack)!=marked.end())
    {
        return 0;
    }
    else
        marked.insert(hashTopStack);

    std::string R;
    std::string op = boost::any_cast<std::string>(nameDomain[n->r1]) ;
    std::string instruction = n->inst;

    /*Case 1:
        jmp instruction
            move to the jump address
    */
    if(strcmp(n->inst,"jmp")==0)
    {


        try
        {
            /*create a transition rule*/
        R = createRule(addr, getTopStack(stack_value), n->next1, getTopStack(stack_value),"",-1,-1);
        fprintf(f, "%s\n",R.c_str());

        /*move to the next address*/
        traverse(stack_value, n->next1,depth,f);
        }
        catch(int e )
        {
            std::cout << "jump\n";
            throw;
        }

        return 0;
    }
    else if(boost::starts_with(instruction, "j"))    //cjmp instruction (conditional jump)
    {

        try
        {
        /*create transition rules*/
        R = createRule(addr, getTopStack(stack_value), n->next1, getTopStack(stack_value),"",-1,-1);
        fprintf(f, "%s\n",R.c_str());
        R = createRule(addr, getTopStack(stack_value), n->next2, getTopStack(stack_value),"",-1,-1);
        fprintf(f, "%s\n",R.c_str());


        /*move to the conditional address*/
        traverse(stack_value, n->next1,depth,f);
        /*move to the next address*/
        traverse(stack_value, n->next2,depth,f);

        }
        catch(int e )
        {
            std::cout << "jump\n";
            throw;
        }


        return 0;
    }

    /*Case 2:
        push instruction
            update the stack_value
            move to the next address*/
    if(instruction.compare("push")==0)
    {

        try
        {
                /*create a stack symbol*/
        std::string sreg = boost::lexical_cast<string>(n->r1);
        std::string s = sreg+"@";
        s +=saddr;

        /*create transition rules*/
        R = createRule(addr, getTopStack(stack_value), n->next1, s,getTopStack(stack_value),-1,-1);
        fprintf(f, "%s\n",R.c_str());

        /*update the stack*/
        stack_value.push(s.c_str());

        /*move to the conditional address*/
        traverse(stack_value, n->next1,depth,f);
        }
        catch(int e )
        {
            std::cout << "push\n";
            throw;
        }



        return 0;

    }

    /*Case 3:
        a sequence of push instructions
            update the stack_value
            move to the next address
    */
    if(op.compare("esp")==0 &&
            ((instruction.compare("sub")==0 && n->v2>0) ||(instruction.compare("add")==0&& n->v2<0)))
    {

        try{
        long i= n->v2<0?n->v2*-1/4:n->v2/4;
        std::string sreg = boost::lexical_cast<string>(0);
        std::string s = sreg+"@";
        s +=saddr;
        /*create a transition rule*/
        R = createRule(addr, getTopStack(stack_value), addr, s,getTopStack(stack_value),-1,i-1);
        fprintf(f, "%s\n",R.c_str());
        i--;

        while(i>0)
        {

            /*update the stack*/
            stack_value.push(s.c_str());

            if(i>1)
            {
                /*create a transition rule*/
                R = createRule(addr, getTopStack(stack_value), addr, s,getTopStack(stack_value),i,i-1);
                fprintf(f, "%s\n",R.c_str());
            }
            else
            {
                /*create a transition rule*/
                R = createRule(addr, getTopStack(stack_value), n->next1, s,getTopStack(stack_value),1,-1);
                fprintf(f, "%s\n",R.c_str());
            }


            i--;
        }
        /*move to the conditional address*/
        traverse(stack_value, n->next1,depth,f);

        }
        catch(int e )
        {
            std::cout << "esp\n";
            throw;
        }
        return 0;
    }

    /*Case 4:
        pop instruction
            update the stack_value
            move to the next address*/
    if(instruction.compare("pop")==0)
    {
        try{
        /*there is no stack symbol to pop*/
        if(stack_value.empty())
            return 0;
        /*create a transition rule*/
        R = createRule(addr, getTopStack(stack_value), n->next1, "","",-1,-1);
        fprintf(f, "%s\n",R.c_str());

        /*update the stack*/
        if(!stack_value.empty())
            stack_value.pop();

        /*move to the conditional address*/
        traverse(stack_value, n->next1,depth,f);
        }
        catch(int e )
        {
            std::cout << "pop\n";
            throw;
        }
        return 0;

    }

    /*Case 5:
        a sequence of pop instructions
            update the stack_value
            move to the next address
    */
    if(op.compare("esp")==0 &&
            ((instruction.compare("sub")==0 && n->v2<0) ||(instruction.compare("add")==0&& n->v2>0)))
    {
        try{
        /*there is no stack symbol to pop*/
        if(stack_value.empty())
            return 0;
        long i= n->v2<0?n->v2*-1/4:n->v2/4;

        /*create a transition rule*/
        R = createRule(addr, getTopStack(stack_value), addr, "","",-1,i-1);
        fprintf(f, "%s\n",R.c_str());
        i--;

        while(i>0 )
        {
            if(!stack_value.empty())
                stack_value.pop();


            if(i>1)
            {
                /*create a transition rule*/
                R = createRule( addr, getTopStack(stack_value), addr, "","",i,i-1);
                fprintf(f, "%s\n",R.c_str());
            }
            else
            {
                /*create a transition rule*/
                R = createRule( addr, getTopStack(stack_value), n->next1, "","",1,-1);
                fprintf(f, "%s\n",R.c_str());
            }

            i--;
        }
        /*move to the conditional address*/
        traverse(stack_value, n->next1,depth,f);
        }
        catch(int e )
        {
            std::cout << "esp\n";
            throw;
        }
        return 0;
    }

    /*Case 6:
        return instruction
            update stack_value
            stop at this address*/
    if(boost::starts_with(instruction, "ret"))
    {
        try{
        /*there is no return address*/
        if(stack_value.empty())
            return 0;
        /*get the return address*/
        std::string ret = getTopStack(stack_value);
        ret = replace(ret, "S","-");
        std::vector<std::string> sp = split(ret,"@");
        //std::cout<< "\t\t "<< ret <<"\n";
        long retV = boost::lexical_cast<long>(sp.at(0)); //return address

        if(isValid(retV)==NULL)
            return 0;
        //retV = n->next1;


        /*pop the return address and stack symbols (if request)*/
        int i=0;
        if(n->v1>0)
            i+=n->v1/4;
        if(i==0)
        {
            /*create a transition rule*/
            R = createRule(addr, getTopStack(stack_value), retV, "","",-1,-1);
            fprintf(f, "%s\n",R.c_str());
            if(!stack_value.empty())
                stack_value.pop();
        }
        else
        {
            /*create a transition rule*/
            R = createRule(addr, getTopStack(stack_value), addr, "","",-1,i);
            fprintf(f, "%s\n",R.c_str());

            if(!stack_value.empty())
                stack_value.pop();
        }

        while(i>0 )
        {
            if(i>1)
            {
                /*create a transition rule*/
                R = createRule(addr, getTopStack(stack_value), addr, "","",i,i-1);
                fprintf(f, "%s\n",R.c_str());
            }
            else
            {
                /*create a transition rule*/
                R = createRule(addr, getTopStack(stack_value), retV, "","",1,-1);
                fprintf(f, "%s\n",R.c_str());
            }
            i--;
            if(!stack_value.empty())
                stack_value.pop();
        }

        /*move to the entry point of the function*/
        traverse(stack_value, retV,depth+1,f);
        }
        catch(int e )
        {
            std::cout << "ret\n";
            throw;
        }
        return 0;
    }

    /*Case 7:
        call instruction
            move to the entry point of the function
            move to the next address
        */
    if(instruction.compare("call")==0)
    {
        try{
        /*create stack symbol with the return address*/
        std::string sreg = boost::lexical_cast<string>(n->next1);
        std::string s = sreg+"@";
        s +=saddr;

        if(n->v1>0  && !n->api)
        {
            /*create a transition rule*/
            R = createRule(addr, getTopStack(stack_value), n->v1, s,getTopStack(stack_value),-1,-1);
            fprintf(f, "%s\n",R.c_str());

            /*if the entry point of the callee cannot be found in the program
                move to the next instruction*/
            if(isValid(n->v1)==NULL)
            {
                R = createRule(n->v1, s, n->next1, "","",-1,-1);
                fprintf(f, "%s\n",R.c_str());
            }
            else
            {
                stack_value.push(s.c_str());
                /*move to the entry point of the function*/
                traverse(stack_value, n->v1,depth-1,f);
            }


        }
        else if(!n->api)
        {

            std::string ef = getAddr(op.c_str());

            long lef = hexToDecimal(ef.c_str()); //the entry point of function

            /*create a transition rule*/
            R = createRule(addr, getTopStack(stack_value), lef, s,getTopStack(stack_value),-1,-1);
            fprintf(f, "%s\n",R.c_str());

            /*if the entry point of the callee cannot be found in the program
                move to the next instruction*/
            if(isValid(lef)==NULL)
            {
                R = createRule(lef, s, n->next1, "","",-1,-1);
                fprintf(f, "%s\n",R.c_str());

            }
            else
            {
                stack_value.push(s.c_str());
                /*move to the entry point of the function*/
                traverse(stack_value, lef,depth-1,f);
            }
        }
        else

            /*if a call to a API function, move to next address*/
            if(n->api)
            {

                std::string APIName = boost::lexical_cast<std::string>(n->r1);

                funcType* mf = getValue(op,mfapi);

                int nArgs = mf==NULL?0:mf->nArgs;
                if(nArgs<=0)
                {
                    /*create a transition rule*/
                    R = createRule(decimalToHex(addr), getTopStack(stack_value),APIName,s, getTopStack(stack_value),-1,-1);
                    fprintf(f, "%s\n",R.c_str());
                    /*create a transition rule*/
                    R = createRule(APIName, s,decimalToHex(n->next1), "","",-1,-1);
                    fprintf(f, "%s\n",R.c_str());
                }
                else
                {

                    R = createRule(decimalToHex(addr), getTopStack(stack_value),APIName, s,getTopStack(stack_value),-1,-1);
                    fprintf(f, "%s\n",R.c_str());

                    int ni = nArgs;
                    R = createRule(APIName, s,APIName, "","",-1,ni);
                    fprintf(f, "%s\n",R.c_str());

                    /*pop all parameter from the stack for API functions*/
                    while(ni>1 )
                    {

                        R = createRule(APIName, getTopStack(stack_value),APIName, "","",ni,ni-1);
                        fprintf(f, "%s\n",R.c_str());

                        if(!stack_value.empty())
                            stack_value.pop();

                        ni--;
                    }

                    R = createRule(APIName, getTopStack(stack_value),decimalToHex(n->next1), "","",ni,-1);
                    fprintf(f, "%s\n",R.c_str());
                    if(!stack_value.empty())
                        stack_value.pop();
                }
                /*move to the next address*/
                traverse(stack_value, n->next1,depth,f);
            }
        }
        catch(int e )
        {
            std::cout << "call\n";
            throw;
        }
        return 0;
    }

    /*Case 8:
        other instructions
            move to next address*/

    try{
    /*create a transition rule*/
    R = createRule(addr, getTopStack(stack_value), n->next1, getTopStack(stack_value),"",-1,-1);
    fprintf(f, "%s\n",R.c_str());

    /*move to the next address*/
    traverse(stack_value, n->next1,depth,f);
    }
    catch(int e )
        {
            std::cout << "others\n";
            throw;
        }
    return 0;
}


void createPDSFile(std::string fpds, std::string fout, std::string addr, std::string sym0)
{
    std::fstream outfile;
    outfile.open(fout, std::fstream::out);
        assert(outfile);

        std::fstream infile;
        infile.open(fpds, std::fstream::in);
        //assert(infile);
        if(infile==NULL)
            std::cout << "File not found\n";


        std::string line;
        line = "(" +addr;
        line += " <"+sym0+">)";
        outfile << line << "\n";

        //std::cout << line <<"\n";

        std::getline(infile, line);

        while (std::getline(infile, line))
        {
            outfile << line << "\n";
        }
        infile.close();
        outfile.close();
}


void print_DEPGRAPH(std::string filename, gEdgeType &edge,gNodeType &api, bool abstractG)
{
    //std::cout <<"\tSave to file " << filename << "\n";
    std::string vname="Eapi";
    vname = abstractG?"_Aeapi":"_Eapi";
    std::fstream out;
    out.open(filename+vname+"Edge",std::fstream::out);
    assert(out);
    for(gEdgeType::iterator it = edge.begin();it!=edge.end();it++)
    {
        edgeType* e = it->second;
        out << it->first << "\t";;
        out << getAPIFunctionName(e->e0) << "\t";
        out << getAPIFunctionName(e->e1) << "\t";
        out << e->f;
        if(e->var==NULL)
        {
            out <<"\n";
            continue;
        }


        for(stringSet::iterator it1 = e->var->begin();it1!=e->var->end();it1++)
        {
            out << "\t"<<*it1;
        }

        out <<"\n";
    }
    out.close();


    out.open(filename+vname+"Node",std::fstream::out);
    assert(out);
    for(gNodeType::iterator it = api.begin();it!=api.end();it++)
    {
        nodeType* n = it->second;
        out << it->first<<"\t";
        out << getAPIFunctionName(n->n);
        if(n->var==NULL)
        {
            out <<"\t"<<n->f;
            out<<"\n";
            continue;
        }

        for(stringSet::iterator it1 = n->var->begin();it1!=n->var->end();it1++)
        {
            out <<"\t"<<*it1;
        }
        out <<"\t"<<n->f;
        out <<"\n";
    }
    out.close();
}

void computePostStar(entryPoint* start, char* fn,bool abstractG)
{
    if(abstractG)
        std::cout << "Compute Abstract Extended API call graph...\n";
    else
        std::cout << "Compute Extended API call graph...\n";
    long startPoint = start->e;
    entryPoint* eStart = start;

    gEdgeType edge;
    gNodeType api;
    int count =0;
    while(eStart!=NULL)
    {

        std::string addr = decimalToHex(eStart->e);
        std::string filename =poststarfile+addr;

        createPDSFile(fn,filename,addr,"S1@S1");

        std::string mopedCMD;
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
        mopedCMD="moped_src\\moped.exe -s0 -r0 -pFE "+filename;
        #else
        mopedCMD="./moped_src/moped -s0 -r0 -pFE "+filename;
        #endif
        //mopedCMD = "moped/moped.exe -s0 -r0 -pFE "+filename;
        //std::cout << "\tExecute: "<< mopedCMD << "\n";
         mopedCMD +=" :q";
        int status = system(mopedCMD.c_str());
        if( status !=0)
        {
            eStart = eStart->next;
            std::remove(filename.c_str());
            continue;
        }

        computeTheta(filename);

        computeDEPGraph(filename,edge,api,abstractG);

        eStart = eStart->next;
        std::remove(filename.c_str());
        std::remove((filename+"post").c_str());
        std::remove((filename+"_dep").c_str());
        std::remove((filename+"_fdep").c_str());

        if(count > CallDepth)
            break;
        count++;

    }

    print_DEPGRAPH(examfile,edge,api,abstractG);

}

void print_poststart(std::string filename)
{
    //std::cout << "\tSave to "<< filename << "\n";

    std::fstream outfile;
    outfile.open(filename,std::fstream::out);
    assert(outfile);


    for(ruleType::iterator it = mTrans.begin(); it != mTrans.end(); it++)
    {
        std::string n = it->first;

        if(boost::contains(n,"_"))
            continue;
        tranType* trans = it->second;
        outfile << n << "--";
        for(tranType::iterator it1 = trans->begin(); it1!=trans->end(); it1++)
        {
            std::string s = it1->first;
            ruleSet* sSet = it1->second;
            outfile  << s <<"-->";
            for(stringSet::iterator it2 = sSet->s.begin(); it2!=sSet->s.end(); it2++)
            {
                std::string q = *it2;
                outfile << q ;
                outfile << "[";
                for(varType::iterator it3 = sSet->var.begin(); it3!=sSet->var.end(); it3++)
                {
                    stringSet* strSet = it3->second;
                    if(strSet->size()<1)
                        continue;
                    outfile << it3->first<< "={";

                    for(stringSet::iterator it4 = strSet->begin(); it4!=strSet->end(); it4++ )
                    {
                        outfile << *it4<<";";
                    }
                    outfile << "}";
                }
                outfile << "]";
            }
            outfile << "\t"<<"--";
        }
        outfile << "\n";
    }
    outfile.close();

}




void print_DEP(std::string filename)
{
    //std::cout << "\tSave Dep to "<< filename << "\n";

    std::fstream outfile;
    outfile.open(filename,std::fstream::out);
    assert(outfile);
    int count=0;


    for(ruleType::iterator it = mTrans.begin(); it != mTrans.end(); it++)
    {
        std::string n = it->first;
        int nArgs = 0;
        if(!boost::starts_with(n,"^") && !boost::contains(n,"_"))
        {

            try
            {
                n = replace(n,"S","-");

                std::string n1;
                try
                {

                        long nadr = atol(n.c_str());
                        if(nadr!=0)
                        n1 = boost::any_cast<std::string>(nameDomain[nadr]);
                        else
                            n1 = n;


                }
                catch(boost::bad_lexical_cast &)
                {
                    n1 = n;
                }



                funcType* mf = getValue(n1,mfapi);
                n = mf==NULL?n1:mf->name;
                nArgs = mf==NULL?0:mf->nArgs;
                if(mf==NULL)
                    continue;
                //std::cout << n <<"\t" << n1 <<"\t" << mf->nArgs <<"\n";
            }
            catch(exception &e)
            {
                n=it->first;
                continue;
            }

        }
        else
            continue;


        count++;

        tranType* trans = it->second;
        outfile << it->first <<"\t" <<n <<"\t"<< nArgs ;
        if(nArgs==0)
        {
            outfile<<"\n";
            continue;
        }


        ruleSet* sSetv =NULL; //collecting all data dependence of the parameter of all transitions
        bool comp=false;


        int printYet = 0;
        for(tranType::iterator it1 = trans->begin(); it1!=trans->end(); it1++)
        {
            std::string s = it1->first;
            if(printYet==0){
                    outfile << "\t" << s ;
                    printYet++;
            }

            ruleSet* sSet = it1->second;
            ruleSet* sSet1 = new ruleSet; //collecting data dependence of the parameter for each transition
            for(varType::iterator it3 = sSet->var.begin(); it3!=sSet->var.end(); it3++)
            {
                /*if it is a parameter*/
                if(!boost::starts_with(it3->first,"v"))
                    continue;
                stringSet* strSet = it3->second;
                for(stringSet::iterator it4 = strSet->begin(); it4!=strSet->end(); it4++ )
                {
                    std::string reg1 = split(*it4,"@").at(0);
                    std::string addr1 = split(*it4,"@").at(0);
                    /*Compute the dependence of parameters at the entry point of a API function*/
                    strSet = computeDep(reg1, addr1,strSet);

                }
                //update the current strSet
                sSet1->var[it3->first] = strSet;
            }
            if(sSetv==NULL)
                sSetv = sSet1;
            /*copy data dependence of each transition to sSetv*/
            copyS0toS1(sSet1,sSetv,"", comp);
        }
        /*print out the dependence function*/

        outfile << "\t(";

        for(varType::iterator it1 = sSetv->var.begin(); it1!=sSetv->var.end(); it1++)
        {
            outfile << it1->first<<"={";
            stringSet* strSet = it1->second;
            for(stringSet::iterator it4 = strSet->begin(); it4!=strSet->end(); it4++ )
            {
                outfile << *it4<<";";
            }
            outfile <<"},";
        }
        outfile << ")\n";
    }
    outfile.close();
    //std::cout << "\t\t#APIs: "<<count << "\n\n";
}

void readPoststar(std::string filename)
{
    std::fstream infile;
    infile.open(filename, std::fstream::in);
    //assert(infile);
    if(infile==NULL){
        std::cout << "File not found\n";
    }
    std::string line;
    while(std::getline(infile, line))
    {
        if(line.length()==0)
            continue;
        std::vector<std::string> sp = split(line," ");

        std::string n = sp.at(0);
        std::string s = sp.at(1);
        std::string q = sp.at(2);

        s = removeChar(s,'[');
        s = removeChar(s,']');
        s = removeChar(s,'-');
        s = removeChar(s,'>');

        /*update transition rules of a state*/
        tranType* trans = getValue(n,mTrans);
        ruleSet* sSet;
        if(trans==NULL)
        {
            trans = new tranType;
        }
        sSet= getValue(s,*trans);
        if(sSet==NULL)
            sSet = new ruleSet;
        sSet->s.insert(q);
        (*trans)[s]=sSet;
        mTrans[n]=trans;

        //std::cout << n <<"\t" << s <<"\t"<<q<<"\n";
    }
    infile.close();

}

ruleSet* &copyS0toS1(ruleSet* &sSet0, ruleSet* & sSet1,std::string skip, bool&comp)
{
    for(varType::iterator it2 =sSet0->var.begin(); it2!=sSet0->var.end(); it2++)
    {
        std::string reg1 = it2->first;

        if(skip.length()>0 && boost::starts_with(reg1,skip))
            continue;
        stringSet* strSet1 = getValue(reg1, sSet1->var);
        if(strSet1==NULL)
            strSet1 = new stringSet;
        int l = strSet1->size();
        stringSet* strSet0 = it2->second;
        for(stringSet::iterator it3 = strSet0->begin(); it3!=strSet0->end(); it3++)
        {
            strSet1->insert(*it3);
        }

        sSet1->var[reg1]=strSet1;
        if(l<strSet1->size())
            comp = true;
    }
    return sSet1;
}

stringSet* &computeDep(std::string reg,std::string addr, stringSet* &ret)
{
    tranType* trans = getValue(addr, mTrans);
    if(trans==NULL)
        return ret;
    /*Dep is an union of theta (var) function of every rule started from addr*/
    for(tranType::iterator it = trans->begin(); it!=trans->end(); it++)
    {
        ruleSet* sSet = it->second;
        stringSet* strSet = getValue(reg, sSet->var);
        if(strSet==NULL)
            continue;
        for(stringSet::iterator it1 = strSet->begin(); it1!=strSet->end(); it1++)
        {
            std::string sym = *it1;
            int l=ret->size();
            ret->insert(sym);

            /*check if the sym exists or not*/
            if(l>=ret->size())
                continue;
            //std::cout << sym <<"\n";
            std::string reg1 = split(sym,"@").at(0);
            std::string addr1 = split(sym,"@").at(2);
            ret = computeDep(reg1,addr1,ret);
            //std::cout << ret->size();
        }
    }
    return ret;
}

/**
Find n topmost stack symbols
    in the function call
        in order to evaluate the parameters.
*/
void findStackSymbol(std::string laddr, int n, ruleSet* & sSet1)
{
    if(n<=0)
        return 0;

    tranType* trans = getValue(laddr,mTrans);
    std::string para = "v"+ boost::lexical_cast<std::string>(n);
    if(trans!=NULL)
    {
        for(tranType::iterator it = trans->begin(); it!=trans->end(); it++)
        {
            std::string sym = it->first;
            /*recover the variable's name and its address*/
            std::vector<std::string> sp = split(sym,"@");
            sym = replace(sp.at(0),"S","-"); //the negative sign is replaced by S
            long t = atol(sym.c_str());
            std::string reg = boost::any_cast<std::string>(nameDomain[t]);
            t = atol(sp.at(1).c_str());
            std::string addr = decimalToHex(t);

            //std::cout << "\t"<< para <<" <- "<<reg <<"@"<<addr<< "\n";

            ruleSet* sSet = it->second;
            stringSet* strSet = getValue(para,sSet1->var);
            if(strSet==NULL)
                strSet = new stringSet;

            node * loc = isValid(t);
            std::string value="0";
            if(loc!=NULL)
            {
                value = boost::lexical_cast<std::string>(loc->v1);
            }
            strSet->insert(reg+"@"+value+"@"+addr);
            for(stringSet::iterator it1 = sSet->s.begin(); it1!=sSet->s.end(); it1++)
            {
                strSet=computeDep(reg, addr, strSet);
                sSet1->var[para] = strSet;
                findStackSymbol(*it1, n-1,sSet1);
            }

            //(*trans)[sym] = sSet;
            //trans[laddr] = trans;
            sSet1->var[para] = strSet;


            /*print strSet/
            strSet = getValue(para,sSet1->var);
            for(stringSet::iterator it1 = strSet->begin();it1 !=strSet->end();it1++)
            {
                std::cout << "\t\t"<< *it1 << "\n";
            }
            /* * */
        }
    }
}

void find_ith_Symbol(std::string laddr,std::string para, int i,ruleSet* &sSet1,bool&comp)
{
    tranType* trans = getValue(laddr,mTrans);
    if(trans!=NULL)
    {
        for(tranType::iterator it = trans->begin(); it!=trans->end(); it++)
        {
            std::string sym = it->first;

            /*recover the variable's name and its address*/
            std::vector<std::string> sp = split(sym,"@");
            sym = replace(sp.at(0),"S","-"); //the negative sign is replaced by S
            long t = atol(sym.c_str());
            if(t==-1)
                continue;
            std::string reg = boost::any_cast<std::string>(nameDomain[t]);
            t = atol(sp.at(1).c_str());
            std::string addr = decimalToHex(t);


            ruleSet* sSet = it->second;

            if(i>0)
            {
                for(stringSet::iterator it1 = sSet->s.begin(); it1!=sSet->s.end(); it1++)
                {
                    find_ith_Symbol(*it1,para, i-1,sSet1,comp);
                }
            }
            else
            {
                node * loc = isValid(t);
                if(loc!=NULL)
                {
                    stringSet* strSet = getValue(para,sSet1->var);
                    if(strSet==NULL)
                        strSet = new stringSet;
                    int l = strSet->size();
                    std::string value = boost::lexical_cast<std::string>(loc->v1);
                    strSet->insert(reg+"@"+value+"@"+addr);
                    strSet=computeDep(reg, addr, strSet);
                    sSet1->var[para] = strSet;
                    if(l>strSet->size())
                        comp=true;
                    //std::cout << laddr<< "\t\t"<<para << ":"<<reg <<"@"<<value<<"@"<<addr<<"\n";
                }
            }



        }
    }
}

/**
Update the data dependence function theta of the transition rule
*/
void updateTheta(ruleSet* &sSet0,ruleSet* &sSet1,std::string &laddr,std::string &sym0,
                 std::string &raddr,std::string &sym1,bool &comp)
{



    /*get the instruction*/
    //std::cout <<laddr<<":";

    std::string nladdr = split(laddr,"_").at(0);
    /*if(nladdr.compare("405D4B")==0)
    {
        std::cout << nladdr << " "<<raddr <<"\t";

    }*/
    node* n = isValid(hexToDecimal(nladdr.c_str()));
    //std::cout << nladdr << " ";



    if(n!=NULL)
    {
        std::string op = boost::any_cast<std::string>(nameDomain[n->r1]);



        /*constant assignment*/
        if(strcmp(n->inst,"mov")==0 || strcmp(n->inst,"lea")==0 || (n->r2!=0 & n->r1!=0))
        {

            std::string reg1 = boost::any_cast<std::string>(nameDomain[n->r1]);
            std::string reg2 = boost::any_cast<std::string>(nameDomain[n->r2]);
            std::string v2 = boost::lexical_cast<std::string>(n->v2);

            /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    we skip updating the dependence of the modified register reg1*/
            sSet1 = copyS0toS1(sSet0,sSet1,reg1,comp);

            /*in the case of parameters, x = [esp+arg_0] or [esp+c+arg_0]
                arg_0 = (v2-c)/4 specifies the index of symbol on the stack */
            if(boost::starts_with(reg2,"[esp+")&& n->v2>0 )
            {
                std::string sc = split(reg2,"+").at(1);
                sc = replace(sc,"h","");
                int c = hexToDecimal(sc.c_str());
                int i =n->v2;
                if(c>0)
                    i-= c;
                i/=4;
                find_ith_Symbol(nladdr,reg1,i,sSet1,comp);
            }
            else

                /*in the case of parameters, x = [ebp+arg_0] or [ebp+c+arg_0]
                    so we subtract value of ebp, then
                    arg_0 = (v2-c-4)/4 specifies the index of symbol on the stack */
                if(boost::starts_with(reg2,"[ebp+") && n->v2>0)
                {
                    std::string sc = split(reg2,"+").at(1);
                    sc = replace(sc,"h","");
                    int c = hexToDecimal(sc.c_str());
                    int i = n->v2-4;
                    if(c>0)
                        i-= c;
                    i/=4;

                    //int i = (n->v2-4)/4;
                    /*get the function of i-th parameter from the stack*/
                    std::string v ="v"+ boost::lexical_cast<std::string>(i);
                    stringSet* strSet0 = getValue(v,sSet1->var);
                    if(strSet0==NULL)
                        return 0;

                    stringSet* strSet = getValue(reg1,sSet1->var);
                    if(strSet==NULL)
                        strSet = new stringSet;
                    int l = strSet->size();
                    for(stringSet::iterator it=strSet0->begin(); it!=strSet0->end(); it++)
                    {
                        strSet->insert(*it);
                    }
                    sSet1->var[reg1]=strSet;
                    if(l<strSet->size())
                        comp=true;
                }
                else
                {
                    /*in normal case*/
                    stringSet* strSet = getValue(reg1,sSet1->var);
                    if(strSet==NULL)
                        strSet = new stringSet;
                    int l = strSet->size();
                    std::string vreg = reg2+"@"+v2+"@"+laddr;
                    strSet->insert(vreg);
                    strSet = computeDep(reg2,laddr,strSet); //compute Dep where defined reg2 (laddr)
                    sSet1->var[reg1]=strSet;
                    if(l<strSet->size())
                        comp=true;
                }

            return 0;
        }

        /*pop instruction*/
        if(strcmp(n->inst,"pop")==0)
        {
            std::string reg1 = boost::any_cast<std::string>(nameDomain[n->r1]);
            std::string vreg = sym0;
            vreg = replace(vreg, "S","-");
            std::vector<std::string>sp = split(vreg,"@");
            int hashname = atoi(sp.at(0).c_str());
            std::string reg2 = hashname!=0?boost::any_cast<std::string>(nameDomain[hashname]):sp.at(0);
            hashname = atoi(sp.at(1).c_str());
            vreg = hashname!=0?boost::any_cast<std::string>(nameDomain[hashname]):sp.at(1);
            stringSet* strSet = getValue(reg1,sSet1->var);
            if(strSet==NULL)
                strSet = new stringSet;
            int l = strSet->size();

            /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    skip updating reg1 because it is modified*/
            sSet1 = copyS0toS1(sSet0,sSet1,reg1,comp);

            //strSet->insert(reg2+"@"+vreg) ;
            strSet = computeDep(reg2,vreg,strSet);

            sSet1->var[reg1]=strSet;
            if(l<strSet->size())
                comp=true;

            return 0;
        }

        /*a sequence of pop instruction*/
        if(op.compare("esp")==0 &&
                ((strcmp(n->inst,"sub")==0 && n->v2<0) ||(strcmp(n->inst,"add")==0&& n->v2>0)))
        {
            /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    */
            sSet1 = copyS0toS1(sSet0,sSet1,"",comp);
        }

        /*push instruction*/
        if(strcmp(n->inst,"push")==0 ||
                (op.compare("esp")==0 &&
                 ((strcmp(n->inst,"sub")==0 && n->v2>0) ||(strcmp(n->inst,"add")==0&& n->v2<0))))
        {

            /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    */
            sSet1 = copyS0toS1(sSet0,sSet1,"",comp);

            /*update the data dependence function of t''*/
            std::string raddrSym1 = "^"+raddr+"~"+sym1+"^";

            tranType* trans2 = getValue(raddrSym1,mTrans);
            if(trans2!=NULL)
            {
                //std::cout << raddrSym1<<" ";
                ruleSet* sSet2 = getValue(sym0,*trans2);
                if(sSet2 !=NULL)
                {
                    sSet2=copyS0toS1(sSet0,sSet2,"",comp);
                    //std::cout << raddrSym1<<" ";
                    //(*trans2)[sym0]=sSet2;
                    //mTrans[raddrSym1]=trans2;
                }
            }

            return 0;
        }

        /*call instruction*/
        /**TODO*/
        if(strcmp(n->inst,"call")==0)
        {
            /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    skip updating the parameters v_* because they will get new values at the call*/
            sSet1 = copyS0toS1(sSet0,sSet1,"v",comp);


            /* */

            std::string efname = boost::any_cast<std::string>(nameDomain[n->r1]);
            //std::cout << efname<<" "<< decimalToHex( n->v1)   <<"\n";
            int nArgs;
            std::string ef;
            ef= efname;
            funcType* temp = getValue(ef,mfapi);
            nArgs = temp==NULL?0:temp->nArgs;
            efname = temp==NULL?efname:temp->name;
            ef = temp==NULL?ef:decimalToHex(temp->addr);
            //std::cout << efname<<"@"<<ef  <<":" << nArgs <<"\n";

            findStackSymbol(laddr, nArgs, sSet1);



            /**/
            /*we update the parameters for the return address*/
            //std::cout << laddr << " "<< sym0 <<" " <<raddr << " "<<sym1 << " "<< sym0 <<"\n";
            std::string strReturnAddr = replace(split(sym1,"@").at(0),"S","-");
            long hashname = atol(strReturnAddr.c_str());

            std::string returnAddr =hashname>0? decimalToHex(hashname):strReturnAddr;
            //std::cout << split(sym1,"@").at(0) <<"\n";
            tranType* trans2 = getValue(returnAddr,mTrans);
            if(trans2!=NULL)
            {

                //ruleSet* sSet2 = getValue(sym0, *trans2);
                //if(sSet2!=NULL)

                for(tranType::iterator it2 = trans2->begin(); it2!=trans2->end(); it2++)
                {
                    ruleSet* sSet2 = it2->second;



                    //std::cout << "\t\t update \n";
                    sSet2=copyS0toS1(sSet0,sSet2,"",comp);


                    if(n->api)
                    {
                        /*dependence function of eax for return function*/
                        stringSet* strSet2 = getValue("eax",sSet2->var);
                        if(strSet2==NULL)
                        {
                            strSet2 = new stringSet;
                        }

                        int l= strSet2->size();
                        for(varType::iterator it0 = sSet1->var.begin(); it0!=sSet1->var.end(); it0++)
                        {
                            std::string s0 = it0->first;

                            if(boost::starts_with(s0,"v"))
                            {
                                //std::cout << "\t"<<s0<<"\n";
                                stringSet* strSet0 = it0->second;
                                for(stringSet::iterator it1 = strSet0->begin(); it1!=strSet0->end(); it1++)
                                {
                                    std::string sss = *it1;
                                    strSet2->insert(sss);
                                }
                            }
                        }
                        if(l<strSet2->size())
                            sSet2->var["eax"]=strSet2;
                    }

                }
            }



            /**/
            return 0;
        }

        /*return instruction*/
        if(boost::starts_with(n->inst,"ret"))
        {

            /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    skip updating the parameters v_* because they are not parameters of the return address*/
            if(boost::starts_with(raddr, nladdr))
            {
                /*the 'fake' transition*/
                sSet1 = copyS0toS1(sSet0,sSet1,"",comp);
            }
            else
            {
                /*the real transition*/
                sSet1 = copyS0toS1(sSet0,sSet1,"v",comp);


            }



            return 0;
        }

        /*other instruction*/
        /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    */
        sSet1 = copyS0toS1(sSet0,sSet1,"",comp);
    }
    else
    {
        /*copy sSet0 to sSet1
                if sSet1 is changed, the value of comp is set to true in the function copyS0toS1
                    */
        sSet1 = copyS0toS1(sSet0,sSet1,"",comp);
    }
}


void computeTheta(std::string filename)
{
    //std::cout << "\tCompute Theta... ";
    readPoststar(filename+"post");

    bool comp = true;
    int iter = 1;
    while(comp)
    {
        //std::cout << iter++ << " ";
        comp=false;
        for(pdsType::iterator it = Lpds.begin(); it!=Lpds.end(); it++)
        {
            pdsRuleSet* ruleS = it->second;
            for(pdsRuleSet::iterator it1 = ruleS->begin(); it1 !=ruleS->end(); it1++)
            {
                pdsRule* r = *it1;
                std::string laddr = r->n0;
                std::string raddr = replace(r->n1,"-","S");
                std::string sym0 = r->s0;
                std::string sym1 = r->s1;

                //std::cout << "\t"<<laddr << " "<<raddr<<"\n";

                /*get transition rules t and t'*/
                tranType* trans0 = getValue(laddr, mTrans);
                tranType* trans1 = getValue(raddr, mTrans);

                if(trans0==NULL || trans1==NULL)
                {
                    //std::cout << "\t"<<laddr<<" "<<sym0 << " "<<raddr<<" "<<sym1<<"\n";
                    continue;
                }



                //std::cout << r->n0 <<" "<< sym0 << "\n";

                ruleSet* sSet0 = getValue(sym0, *trans0);
                ruleSet* sSet1 = getValue(sym1,*trans1);

                /**TODO
                        sym1 = epsilon in pds
                        while sym1 <> epsilon in post star */


                /*sSet ==NULL since there is no transition from the address with this symbol*/
                if(sSet0==NULL )
                    continue;
                if(sSet1==NULL&& sym1.length()>0)
                    continue;

                if(sym1.length()==0)
                {


                    //std::cout <<"\n";
                    for(tranType::iterator it01 = trans1->begin(); it01!=trans1->end(); it01++)
                    {
                        sym1 = it01->first;

                        sSet1 = it01->second;
                        if(sSet1 ==NULL)
                            continue;
                        //std::cout << sym1 << " ";
                        updateTheta(sSet0,sSet1,laddr,sym0,raddr,sym1,comp); //TODO here is the epsilon transition


                        //(*trans1)[sym1]= sSet1;
                    }
                    //std::cout <<"\n";


                }
                else
                {
                    updateTheta(sSet0,sSet1,laddr,sym0,raddr,sym1,comp);


                    //(*trans1)[sym1]= sSet1;

                }
                //mTrans[raddr] =trans1;


            }
        }
    }

    //std::cout <<"\n";
    print_poststart(filename+"_dep");
    print_DEP(filename+"_fdep");
}

std::string getString(std::string line, std::string tag)
{
    std::string ret = removeChar(line, '\t');
    ret = replace(ret, "<"+tag+">","<");
    ret = replace(ret, "</"+tag+">","<");
    ret = removeChar(ret, '<');
    return ret;
}

std::map<std::string, apiType*>  readAPI(std::string filename)
{
    //std::cout << "\tRead APIs...\n";
    std::map<std::string, apiType*> mAPI;
    std::fstream outfile;
    outfile.open(filename+".out", std::fstream::out);
    assert(outfile);

    std::fstream infile;
    infile.open(filename+".xml", std::fstream::in);
    if(infile==NULL)
    {
        std::cout << "missing xml file!\n";
    }
    //assert(infile);
    std::string line;
    while(std::getline(infile, line))
    {
        line = removeChar(line, '\t');

        if(boost::starts_with(line,"<function>"))
        {

            std::getline(infile, line);
            std::string name = getString(line,"name");

            std::getline(infile, line);
            std::string dll = getString(line,"dll");

            std::getline(infile, line);
            std::string desc = getString(line,"description");

            int nArgs=0;

            //std::cout << name << "\n";
            outfile << name << "\n";
            outfile << "&" <<dll << "\n";
            outfile << "&" <<desc << "\n";


            std::getline(infile, line);
            line = removeChar(line, '\t');
            if(boost::starts_with(line,"<arguments>"))
            {

                while(std::getline(infile, line))
                {
                    line = removeChar(line, '\t');
                    if(boost::starts_with(line,"<argument>"))
                    {
                        std::getline(infile, line);
                        std::string argName = getString(line,"name");
                        std::getline(infile, line);
                        std::string argDesc = getString(line,"description");

                        outfile << "\t" <<argName <<":"<<argDesc<<"\n";
                        nArgs++;
                    }

                    if(boost::starts_with(line,"</arguments>"))
                    {
                        std::getline(infile, line);
                        line = removeChar(line, '\t');

                        outfile << "@"<<nArgs<<"\n";
                        break;
                    }


                }
            }

            std::string Fret = getString(line,"returns");
            outfile << "@"<< Fret<<"\n";

            apiType* s = new apiType;
            s->name = name;
            s->desc = desc;
            s->ret = Fret;
            s->nArgs = nArgs;
            mAPI[name]=s;

        }
    }

    infile.close();
    outfile.close();
    return mAPI;
}

void readProgramAPI(std::string filename)
{
    //std::cout << "Reading functions...\n";
    std::fstream infile;
    infile.open(filename+"_Func.out", std::fstream::in);
    if(infile==NULL)
        std::cout << "File not found\n";
    //assert(infile);
    std::string line;
    while(std::getline(infile, line))
    {
        std::vector<std::string> sp = split(line, "\t");
        long addr = atol(sp.at(0).c_str());
        std::string saddr = decimalToHex(addr);
        std::string name = sp.at(1);
        int args = atoi(sp.at(2).c_str());
        funcType* f = new funcType;
        f->name = name;
        f->nArgs = args;
        f->addr = addr;
        f->api = false;
        mfapi[name] = f;
        mfapi[saddr] = f;
    }
    infile.close();

    /**Get API description from MSDN*/
    std::map<std::string, apiType*> mAPI = readAPI(apiFile);


    infile.open(filename+"_API.out", std::fstream::in);
    if(infile==NULL)
    {
        std::cout << "API file not found!\n";
        //exit(0);
    }

    while(std::getline(infile, line))
    {
        std::vector<std::string> sp = split(line,"\t");
        if(sp.size()<2)
            continue;
        long addr = atol(sp.at(0).c_str());
        std::string saddr = decimalToHex(addr);

        int args = 0;

        std::string name = sp.at(1);
        if(boost::starts_with(name,"__imp_"))
            continue;

        funcType* f= getValue(name, mfapi);
        if(f==NULL)
        {
            f = new funcType;
            f->name = name;
            f->nArgs = args;
            f->addr = addr;
        }

        std::string name1 = getAPIFunctionName(name);
        apiType* r = getValue(name1, mAPI);
        if(r!=NULL)
        {
            f->nArgs = r->nArgs;
            f->api = true;
        }

        mfapi[name] = f;
        mfapi[saddr] = f;
    }

    infile.close();

    std::fstream outfile;
    outfile.open(temp+apiFile, std::fstream::out);
    assert(outfile);

    for(mFuncType::iterator it = mfapi.begin(); it!=mfapi.end(); it++)
    {
        outfile << it->first;
        funcType* f = it->second;
        outfile <<"\t"<<f->name <<"\t"<<f->nArgs<< "\t"<< f->api<<"\n";
    }
    outfile.close();

    //std::cout << "\t\t#Func: "<<mfapi.size()/2<<"\n";
}

void reduceStartPoint(entryPoint*start)
{
    //std::cout << "Reduce Start Points\n";
    entryPoint* eStart = start->next;
    entryPoint* fStart = start;
    while(eStart!=NULL)
    {
        funcType* mf = getValue(decimalToHex(eStart->e),mfapi);

        if(mf==NULL)
        {
            //std::cout << decimalToHex(eStart->e) <<"\n";
            fStart->next = eStart->next;
            eStart = fStart->next;

            continue;
        }
        else
        {
            //std::cout << mf->name <<"\n";
            if(!boost::starts_with(mf->name,"sub_"))
            {
                //std::cout << decimalToHex(eStart->e) <<"\n";
                fStart->next = eStart->next;
                eStart = fStart->next;
                continue;
            }
        }

        fStart= eStart;
        eStart = fStart->next;
    }
}

std::mutex myMutex;

long reachableCFG(long addr0, std::set<long> & reach,int dep)
{
    if(addr0<1)
        return -1;
    if(reach.find(addr0)!=reach.end() && dep>1)
    {

        return addr0;
    }
    node* n= getValue(mCFG,addr0);

    if(n==NULL)
        return -1;
    reach.insert(addr0);

    reachableCFG(n->next1,reach,dep+1);
    reachableCFG(n->next2,reach,dep+1);

    if(n->api)
        return addr0;
    else
        return -1;
}

/**
Find start point which contains an API call.
**/
void findAPICallLocation(long startPoint,std::set<long> & reachAPI, std::set<long>& ret)
{

    std::set<long> ret2;

    if(startPoint==-1)
        return ;
    node* n = getValue(mCFG, startPoint);
        if(n==NULL)
            return ;

    if(reachAPI.find(startPoint)!=reachAPI.end())
        return ;
    myMutex.lock();
    reachAPI.insert(startPoint);
    myMutex.unlock();
        std::string api = boost::any_cast<std::string>(nameDomain[n->r1]);

        funcType* fapi = getValue(api,mfapi);
        if(fapi==NULL ||
                boost::starts_with(fapi->name, "sub_")||
                    boost::starts_with(fapi->name, "loc_"))
        {

            findAPICallLocation(n->next1, reachAPI,ret);
            findAPICallLocation(n->next2, reachAPI,ret2);

        }else
        {
            myMutex.lock();
            ret.insert(startPoint);
            myMutex.unlock();
        }
    myMutex.lock();
     for(std::set<long>::iterator i=ret2.begin();i!=ret2.end();i++)
                ret.insert(*i);
    //std::cout << ret.size() << " ";
    myMutex.unlock();
    //return ret;

}


std::set<long> getStartAPI(entryPoint* eStart)
{
    int c= 0;
    entryPoint* s= eStart;
    while(s!=NULL)
    {
        c++;
        s=s->next;
    }
    if(c>CallDepth) c = CallDepth;

    std::set<long> ret;
    std::set<long> reachAPI;
    //startTime = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now()-startTime;
    std::thread threads[c];
    int i=0;
    while(eStart!=NULL && i < c)
    {

        //startTime = std::chrono::system_clock::now();
        threads[i]=std::thread(findAPICallLocation,eStart->e, std::ref(reachAPI),std::ref(ret));
        //findAPICallLocation(eStart->e, reachAPI,ret );

        eStart = eStart->next;
        //elapsed_seconds = std::chrono::system_clock::now()-startTime;
        i++;
    }

    for(i=0;i<c;i++)
        threads[i].join();

    return ret;
}


/**
Construct API call graph from a start point in CFG.
**/
void searchReachedAPI(bool abstracG, long startPoint, funcType* fapi,node* n,std::set<std::string>& V,std::set<std::string> &E)
{
    std::set<long>reach;
        reachableCFG(startPoint,reach,1);

    std::string vname;
    vname = abstracG?fapi->name: fapi->name+"*"+ boost::lexical_cast<std::string>(startPoint); //abstract API call graph or API call graph
    myMutex.lock();
    V.insert(vname);
    myMutex.unlock();
        for(std::set<long>::iterator it1 = reach.begin();it1 !=reach.end();it1++)
        {
            long addr = *it1;
            node* n1 = getValue( mCFG,addr);
            if(!n1->api)
                continue;
            if(nameDomain.find(n1->r1)==nameDomain.end())
                continue;

            if(n->r1==n1->r1)
                continue;
            std::string api1 = boost::any_cast<std::string>(nameDomain[n1->r1]);

            funcType* fapi1 = getValue(api1,mfapi);

            if(fapi1==NULL ||
                boost::starts_with(fapi1->name, "sub_")||
                    boost::starts_with(fapi1->name, "loc_"))
                continue;
            std::string vname1;
            vname1 = abstracG?fapi1->name:fapi1->name+"*"+boost::lexical_cast<std::string>(addr); //abstract API call graph or API call graph

            //std::lock_guard<std::mutex> guard(myMutex);
            myMutex.lock();
            V.insert(vname1);
            E.insert(vname +"\t" + vname1);
            myMutex.unlock();
        }
        //myMutex.lock();
        //std::cout <<id<<":"<< reach.size()<< " " ;
        //myMutex.unlock();
}

void RunCFGGraph(std::string filename,entryPoint* start, bool abstractG)
{
    std::string sname="_Api";
    if(abstractG)
    {
        std::cout << "Compute Abstract API call graph...\n";
        sname = "_Aapi";
    }
    else
    {
        std::cout << "Compute API call graph...\n";
        sname = "_Api";
    }

    std::fstream out1,out2;
    out1.open(filename+sname+"Node",std::fstream::out);
    out2.open(filename+sname+"Edge",std::fstream::out);
    assert(out1);
    assert(out2);
    std::set<std::string> V;
    std::set<std::string> E;

    std::set<long> startAddr = getStartAPI(start);

    //std::cout << "\t #startAPI:"<< startAddr.size()<<"\n";



    startTime = std::chrono::system_clock::now();


    int c=startAddr.size()>CallDepth?CallDepth:startAddr.size();
    int id=0;
    std::thread threads[startAddr.size()];

    for(std::set<long>::iterator it=startAddr.begin();it!=startAddr.end()
            && id<c
            ;it++)//set timeout=60 seconds
    {
        long startPoint = *it;

        node* n = getValue(mCFG, startPoint);
        if(n==NULL)
            continue;

        std::string api = boost::any_cast<std::string>(nameDomain[n->r1]);

        funcType* fapi = getValue(api,mfapi);
        if(fapi==NULL ||
                boost::starts_with(fapi->name, "sub_")||
                    boost::starts_with(fapi->name, "loc_"))
        {
            continue;
        }

            //std::cout<< startPoint <<" " <<api<<" " << fapi->name<< " " << fapi->nArgs<<" "<< fapi->api<<endl;

        startTime = std::chrono::system_clock::now();


        threads[id]=std::thread(searchReachedAPI,abstractG,startPoint,fapi,n,std::ref(V),std::ref(E));
        id++;
        //searchReachedAPI(abstractG,startPoint,fapi,n,V,E);
    }

    for(int i= 0;i<c;i++)
    {
        threads[i].join();
    }
        std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now()-startTime;
        std::cout << "\t Elapsed time:"<< elapsed_seconds.count()<< "s" <<endl;

    for(std::set<std::string>::iterator it = V.begin();it!=V.end();it++)
    {
        out1 <<*it<<"\n";
    }
    for(std::set<std::string>::iterator it = E.begin();it!=E.end();it++)
    {
        out2 <<*it<<"\n";
    }

    out1.close();
    out2.close();
    //std::cout << "\n";

}


void RunCFGGraph1(std::string filename, entryPoint* start)
{
    std::cout << "Compute CFG graph\n";
    std::cout << "cfg size: " << mCFG.size() <<"\n";
    //std::cout << "d: " << CallDepth<<endl;
    std::fstream out1,out2;
    out1.open(filename+"_cfgAPI",std::fstream::out);
    out2.open(filename+"_cfgEdge",std::fstream::out);
    assert(out1);
    assert(out2);
    std::set<std::string> V;
    std::set<std::string> E;
    std::set<long>reach;
    startTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now()-startTime;
    for(std::map<long, boost::any>::iterator it = mCFG.begin();it!=mCFG.end()
        && elapsed_seconds.count()<=60;it++)
    {
        elapsed_seconds = std::chrono::system_clock::now()-startTime;
        if(reach.find(it->first)!=reach.end())
            continue;
        node* n = boost::any_cast<node*>(it->second) ; //getValue(mCFG, it->first);
//        if(!n->api)
//            continue;
//
//        if(nameDomain.find(n->r1)==nameDomain.end())
//            continue;

        std::string api = boost::any_cast<std::string>(nameDomain[n->r1]);

        funcType* fapi = getValue(api,mfapi);
        if(fapi==NULL ||
                boost::starts_with(fapi->name, "sub_")||
                    boost::starts_with(fapi->name, "loc_"))
            continue;

            //std::cout<< it->first <<" " <<api<<" " << fapi->name<< " " << fapi->nArgs<<" "<< fapi->api<<endl;
            V.insert(fapi->name);

        reachableCFG(it->first, reach,1);

        std::cout << reach.size()<< " " ;//<<"/" << mCFG.size() <<"\n";

        for(std::set<long>::iterator it1 = reach.begin();it1 !=reach.end();it1++)
        {


            long addr = *it1;
            node* n1 = getValue( mCFG,addr);
            if(!n1->api)
                continue;
            if(nameDomain.find(n1->r1)==nameDomain.end())
                continue;

            if(n->r1==n1->r1)
                continue;
            std::string api1 = boost::any_cast<std::string>(nameDomain[n1->r1]);

            funcType* fapi1 = getValue(api1,mfapi);

            if(fapi1==NULL ||
                boost::starts_with(fapi1->name, "sub_")||
                    boost::starts_with(fapi1->name, "loc_"))
                continue;

            V.insert(fapi1->name);
            E.insert(fapi->name +"\t" + fapi1->name);

            //check = hexToDecimal(api1.c_str());
            //if(check==-1)

                //E.insert(api +"\t" + api1);
            //out2 << api << "\t" << api1<<"\n";
        }
    }

        std::cout << "\t Elapsed time:"<< elapsed_seconds.count()<< "s" <<endl;

    for(std::set<std::string>::iterator it = V.begin();it!=V.end();it++)
    {
        out1 <<*it<<"\n";
    }
    for(std::set<std::string>::iterator it = E.begin();it!=E.end();it++)
    {
        out2 <<*it<<"\n";
    }

    out1.close();
    out2.close();
    std::cout << "\n";

}


bool reachable(std::string addr0, std::string addr1)
{
    //std::cout << addr0 <<"\n";
    if(addr1.compare(addr0)==0)
        return true;

    pdsRuleSet* sr = getValue(addr0,Lpds);
    bool ret = false;
    if(sr==NULL)
        return ret;

    for(pdsRuleSet::iterator it = sr->begin();it!=sr->end();it++)
    {
        pdsRule* r = (*it);
        if(marked.find(hashCode(r->n1))==marked.end())
        {
            marked.insert(hashCode(r->n1));
            ret = reachable(r->n1, addr1);
        }

        if(ret)
            break;
    }
    return ret;
}

varType* getbackDep(std::string d)
{
    varType * var = new varType;
    std::vector<std::string> sp = split(d,",");
    int id =1 ;

    for(int i=0;i< sp.size()-1;i++)
    {
        std::vector<std::string> sp1 = split(sp.at(i), "=");


        if(sp1.size()<2)
            continue;
        std::string t = sp1.at(1);
        t = removeChar(t, '{');

        std::vector<std::string> vStr = split(t,";");
        stringSet* strSet = new stringSet;
        for(int i=0;i<vStr.size()-1;i++)
        {
            //std::cout << vStr.at(i) <<"\n";
            strSet->insert(vStr.at(i));
        }
        std::string v= "v"+ boost::lexical_cast<std::string>(id);
        (*var)[v]=strSet;
        id++;
    }
    return var;
}

bool compareSymbol(std::string x, std::string t)
{
    std::vector<std::string> f = split(x,"@");
    std::vector<std::string> g = split(t,"@");
    int v0 = boost::lexical_cast<int>(f[1]);
    int v1 = boost::lexical_cast<int>(g[1]);
    if(v0!=v1)
        return false;
    if(f[0].compare("eax")==0
       || f[0].compare("ebx")==0
       || f[0].compare("ecx")==0
       || f[0].compare("edx")==0
       || f[0].compare("esi")==0
       || f[0].compare("esp")==0
       || f[0].compare("ebp")==0
       || boost::starts_with(f[0],"[")
       )
    {
        if(f[2].compare(g[2])==0)
           return true;
    }else
    {
        return true;
    }
    return false;
}

stringSet*& dataIntersection(varType* f, varType *g, stringSet*& strSet, int nf, int ng)
{
    if(nf==0 || ng ==0)
        return strSet;
    bool ret = false;
    //std::cout <<" ahahah\n";
    for(varType::iterator it = f->begin();it!=f->end();it++)
    {
        stringSet* s = it->second;
        if(s==NULL)
            continue;
        //std::cout << it->first ;
        for(varType::iterator it1= g->begin();it1!=g->end();it1++)
        {
            stringSet* s1 = it1->second;
            if(s1==NULL)
                continue;
            //std::cout <<"\t"<<it1->first <<"\n";
            for(stringSet::iterator sit = s->begin();s->end()!=sit;sit++)
            {
                for(stringSet::iterator sit1 = s1->begin();s1->end()!=sit1;sit1++)
                {

                    ret = compareSymbol(*sit,*sit1);

                    if(ret)
                    {
                        std::string vf = removeChar(it->first,'v');

                        int temp = atoi(vf.c_str());
                        temp = nf -temp+1;

                        vf = boost::lexical_cast<std::string>(temp);

                        std::string vg = removeChar(it1->first,'v');
                        temp = atoi(vg.c_str());
                        temp = ng -temp+1;
                        vg = boost::lexical_cast<std::string>(temp);

                        //std::string vf= it->first;
                        //std::string vg= it1->first;

                        if(strSet==NULL)
                            strSet = new stringSet;
                        std::string str = vf+"="+vg;
                        strSet->insert(str);
                    }
                    //std::cout<<"\t" << it->first <<"\t"<<it1->first <<"\n";
                }


            }
        }
    }
    return strSet;
}

void computeDEPGraph(std::string fn,gEdgeType & edge,gNodeType& api,bool abstractG)
{
    //std::cout <<"\tCompute Dependence Graph\n";

    std::fstream infile;
    infile.open(fn+"_fdep", std::fstream::in);
    //assert(infile);
    if(infile==NULL)
    {
        std::cout << "File not found\n";
    }
    std::string line;
    std::vector<std::string> addrs;
    std::vector<std::string> names;
    std::vector<int> nargs;
    std::vector<std::string> sym0;
    std::vector<varType*> fdeps;
    while(std::getline(infile, line))
    {
        std::vector<std::string> sp = split(line, "\t");

        if(sp.at(1).length()<1)
        //|| boost::starts_with(sp.at(1),"sub_"))
            continue;

        std::string addr = sp.at(0);
        addr = replace(addr, "S","-");
        addrs.emplace_back(addr);
        names.emplace_back (sp.at(1).c_str());
        nargs.emplace_back (atoi(sp.at(2).c_str()));


        if(sp.size()<4)
        {
            sym0.emplace_back("");
            fdeps.emplace_back (new varType);
            //std::cout <<"computeDEPGraph "<<  line << "\n";
            continue;
        }

        sym0.emplace_back(sp.at(3).c_str());
        //std::cout<< line <<"\t" << sp.size()<<"\n";
        fdeps.emplace_back (getbackDep(sp.at(sp.size()-1).c_str()));
    }
    infile.close();




    //std::cout<<addrs.size() <<"\n";

     int A[addrs.size()][addrs.size()];
    for(int i=0;i<addrs.size();i++)
        for(int j=0;j<addrs.size();j++)
            A[i][j]=0;

    for(int i=0;i<addrs.size();i++)
    {
        for(int j=0;j<addrs.size();j++)
        {
            if(i==j)
                continue;
            //std::cout << addrs[i]<<" ?? "<<addrs[j]<<"\n";
            marked.clear();
            marked.insert(hashCode(addrs.at(i)));
            bool  ret= false;

            for(pdsType::iterator it = Lpds.begin();!ret && Lpds.end()!=it;it++)
            {
                pdsRuleSet* rs = it->second;

                for(pdsRuleSet::iterator it1 = rs->begin();!ret && it1!=rs->end();it1++)
                {
                    pdsRule* r = *it1;

                    if(addrs.at(i).compare(r->n0)==0)
                    {
                        //std::cout <<addr<<" "<< addrs.at(i)<<" " << addrs.at(j)<<std::endl;
                        //std::cout << "\t"<<r->n0<<" " << r->n1<<std::endl;
                        ret = reachable(r->n0,addrs.at(j));
                    }
                }
            }
            if(ret)
            {
                    A[i][j]++;
            }

            //std::cout << addrs[i]<<" ?? "<<addrs[j]<<"\n";
        }
    }


    for(int i= 0; i< names.size();i++)
    {
        for(int j=0;j<names.size();j++)
        {
            if(A[i][j]>0)
            {
                std::string str = abstractG?names[i]+"\t"+names[j]:names[i]+"*"+addrs.at(i)+"\t"+names[j]+"*"+addrs.at(j);
                //std::cout << i<<":"<<j <<" "<<str <<"\n";
                edgeType* e = getValue(str,edge);
                if(e==NULL )
                {
                    e= new edgeType;
                    e->f = A[i][j];
                    e->e0 = names[i];
                    e->e1 = names[j];
                    e->var = NULL;

                    if(nargs.at(i)>0 && nargs.at(j) >0)
                        e->var = dataIntersection(fdeps.at(i),fdeps.at(j),e->var,nargs.at(i),nargs.at(j));
                    //std::cout << str <<"\n";
                }

                e->f = e->f >A[i][j]?e->f:A[i][j];
                if(nargs.at(i)==0 && nargs.at(j) ==0)
                {
                    e->var = NULL;
                    edge[str] = e;
                    continue;
                }
                stringSet* strSet =NULL;
                strSet = dataIntersection(fdeps.at(i),fdeps.at(j),strSet,nargs.at(i),nargs.at(j));

                if(e->var==NULL )
                {
                    e->var = strSet;
                }else
                {
                    if(strSet!=NULL)
                    {
                        for(stringSet::iterator it = strSet->begin();it!=strSet->end();it++)
                        {
                            //std::cout << *it <<"\n";
                            e->var->insert(*it);
                        }
                    }

                }

                edge[str] = e;
            }
        }
    }

    for(int i=0;i< names.size();i++)
    {
        nodeType* napi;
        std::string apiname =abstractG?names[i]: names[i]+"*"+addrs.at(i);
        napi = getValue(apiname,api);
        if(napi==NULL)
        {
            napi = new nodeType;
            napi->n = names[i];
            napi->var = NULL;
            napi->f = 1;
        }else
         napi->f ++;
        varType* var = fdeps[i];

        for(varType::iterator it = var->begin();it!=var->end();it++)
        {
            stringSet* strSet = it->second;
            for(stringSet::iterator it1 = strSet->begin();it1!=strSet->end();it1++)
            {
                vector<std::string> sp = split(*it1,"@");
                /**TODO*/
                std::string number = removeChar(sp.at(0),'h');
                long c = atol(number.c_str());
                long v = atol(sp.at(1).c_str());
                if(c==v && std::isdigit(number.c_str()[0]))
                {
                    if(napi->var==NULL)
                        napi->var = new stringSet;
                    std::string vf = removeChar(it->first,'v');

                    int temp = atoi(vf.c_str());
                    temp = nargs[i] -temp+1;

                    vf = boost::lexical_cast<std::string>(temp);
                    std::string str = vf+"="+sp.at(0);
                    napi->var->insert(str);
                }
            }
        }
        api[apiname]=napi;
    }
}


void RunDepGraph(entryPoint* start,bool abstractG)
{
    ///Build the PDS by traversing from multi entry points of the program
    FILE* fp = fopen(pdsfile.c_str(), "w");
    assert(fp);
    long startPoint = start->e;

    entryPoint* eStart = start;

    fprintf(fp,"(%s <S1@S1>)\n",decimalToHex(startPoint));
    std::stack<std::string> stack_value;
    marked.clear();

    //std::cout<<"Generate PDS...\n";
    while(eStart!=NULL)
    {
        startPoint = eStart->e;

        ///stack_value is a simulation stack of the program where p0&0 is the bottom of the stack.
        //itemStack* stack_value = createStackItem("p0",0);

        //std::cout << decimalToHex(startPoint) <<"\n";
        //stack_value.push("");
        try
        {
                traverse(stack_value,startPoint,CallDepth,fp);
        }
        catch(exception &e)
        {
            cout << "Standard exception: " << e.what() << endl;
            //exit(0);
            throw e;
        }
        catch(runtime_error &e1 )
        {
            cout << "runtime exception: " << e1.what() << endl;
            //exit(0);
            throw e1;
        }



        //std::cout << "\t\tstack "<<stack_value.size()<<"\n";

        while(!stack_value.empty())
            stack_value.pop();
        //std::cout << decimalToHex( startPoint) <<"\n";

        //free(stack_value);
        eStart = eStart->next;

    }
    fclose(fp);

    computePostStar(start,pdsfile.c_str(), abstractG);
}



/**
Run the program
name: filename
opt: 0 for eAPIGraph, 1 for APIGraph and 2 for both.
**/
void Run(std::string name,int opt,bool abstractG)
{

    //std::string name ="Trojan.Win32.Zonekiller.a.exe.upx";
    //std::string name = "VirusShare_1e2722e754074fbb0b2ed13d2eb2dddc";
    //std::string name = "P2P-Worm.Win32.Opex.b.exe.upx";   //VBA functions
    //std::string name = "Trojan-Downloader.Win32.Banload.ce.exe";
    //std::string name ="Trojan-Downloader.Win32.Delf.aav.exe"; //no _API.out???

    //std::cout << name <<"\n";
    examfile = name;

    ///CFG create
    entryPoint* start = NULL;
    std::string fname =path+name+"_statements.out";

    mCFG = createCFG(fname.c_str(),&start);
    if(mCFG.size()<1)
        return;

    /*read nameDomain*/
    nameDomain = NAMEDOMAIN();
    print_nameDomain(outputNameDomain);

    /**/
    readJakstabState(path+name);

    /**/

    /**reading the description of API function from program*/
    readProgramAPI(path+name);
    reduceStartPoint(start);
    //assert(start);
    if(start==NULL)
    {
        std::cout <<"Entry point not found!";
    }
    /****/

    fprint_map(mCFG,nameDomain,outputCFG.c_str());

    switch(opt)
    {
        case 0:RunDepGraph(start,abstractG);
        break;
        case 1:RunCFGGraph(name,start,abstractG);
        break;
        case 2:
            RunDepGraph(start,abstractG);
            RunCFGGraph(name,start,abstractG);
            break;
    }






}


/**
Running the program
name is filename
opt specifies the output graph.
**/
void example4(std::string name,int opt,int depth,bool abstractG)
{
    CallDepth = depth;
    std::string cmd;
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
    cmd = "md "+temp;
    system(cmd.c_str());
    #else
    cmd = "mkdir "+temp;
    system(cmd.c_str());
    #endif

    Run(name, opt,abstractG);

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
    cmd = "del "+temp + "\\*.txt";
    system(cmd.c_str());
    cmd ="del "+temp +"\\*_nn";
    system(cmd.c_str());
    system("rd temp");
    #else
    cmd = "rm "+temp + "\\*.txt";
    system(cmd.c_str());
    cmd ="rm "+temp +"\\*_nn";
    system(cmd.c_str());
    system("rm -r temp");
    #endif

}

}

