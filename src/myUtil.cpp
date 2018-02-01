#include"myUtil.hpp"
#include "mycfg.hpp"

namespace myWPDS
{
char* duplicate(const char* s)
{

    if(s==NULL)
        return NULL;
    //find length of s
    int n = strlen(s);
    char *ret = (char*)malloc(n+1);
    memcpy(ret,s,n+1);

    return ret;
}


/// util ///
void fprint_set(std::set<std::string> s,char* fname)
{
    std::ofstream f;
    f.open (fname);
    std::set<std::string>::iterator it;
    for(it=s.begin(); it!=s.end(); it++)
    {
        f << *it << std::endl;
    }
    f.close();
}

void fprint_map(std::map<long, boost::any> s,std::map<int,std::string> nameDomain,char* fname)
{
    std::ofstream f;
    f.open (fname);

    std::map<long, boost::any>::iterator it;
    for(it=s.begin(); it!=s.end(); it++)
    {
        long addr = it->first;
        f <<  decimalToHex(addr)<<"\t";
        node* n = boost::any_cast<node*>(it->second);
        f << n->inst;
        std::string s = boost::any_cast<std::string>(nameDomain[n->r1]);
        if(strlen(s.c_str())>0)
            f << "\t" << s <<"="<<n->v1 ;

        s = boost::any_cast<std::string>(nameDomain[n->r2]);
        if(strlen(s.c_str())>0)
            f <<"\t"<<  s <<"="<<n->v2 <<";";

        //f << var2String(n->varSet)<<"\n";
        f << "\n";
    }
    f.close();
}



char retrieveHexChar(long num)
{

    char tempChar;

    switch(num)
    {

    case 10:
        tempChar = 'A';
        break;

    case 11:
        tempChar = 'B';
        break;

    case 12:
        tempChar = 'C';
        break;

    case 13:
        tempChar = 'D';
        break;

    case 14:
        tempChar = 'E';
        break;

    case 15:
        tempChar = 'F';
        break;
    }
    return tempChar;

}

char* decimalToHex(long number)
{
    if(number==-1 || number==0)
        return "unknown";
    std::string s;
    s="";
    //std::cout<< number<<"\n";
    while(number>0)
    {
        //std::cout<< number<<"\n";
        char tempChar;
        long temp = number % 16;
        number = number/16;


        if (temp >= 10)
        {

            tempChar = retrieveHexChar(temp);
            s += tempChar;

        }

        else if (temp < 10 )
        {


            char str ='0'+temp;
            s += str;

        }
    }

    //std::cout <<s;
    char* ret = (char*)malloc(s.length()+1);
    for (int i = s.length()-1; i >= 0; i--)
    {
        ret[s.length()-i-1] = s[i];

    }
    ret[s.length()]='\0';
    //std::cout <<" "<<ret<<"\n";
    return ret;
}

long hexToDecimal(const char* s)
{
    if(s==NULL)
        return -1;
    int len = strlen(s);
    long i=1,ret=0;
    int j=len-1;
    while(j>=0)
    {
        char c = s[j];
        long t =0;
        if(c<='9'&&c>='0')
            t=c-'0';
        else if(c<='F'&&c>='A')
            t=c-'A'+10;
        else if(c<='f'&&c>='a')
            t=c-'a'+10;
        else
            return -1;
        ret+=i*t;
        i*=16;
        j--;
    }
    //std::cout<<ret<<"\n";
    return ret;
}

std::string replace(std::string input, std::string s, std::string r)
{
    boost::algorithm::replace_all(input,s, r);
    return input;
}



std::string removeSpaces(std::string input)
{
    input.erase(std::remove(input.begin(),input.end(),' '),input.end());
    //char * cstr = new char [input.length()+1];
    //std::strcpy (cstr, input.c_str());
    //return cstr;


    return input;
}

std::string removeChar(std::string input, char r)
{
    input.erase(std::remove(input.begin(),input.end(),r),input.end());
    return input;
}

std::vector<std::string> split(std::string s, std::string c)
{
    std::vector<std::string> ret;
    boost::split(ret,s,boost::is_any_of(c));
    return ret;

}

bool isVar(char* v)
{
    //fix memory
    if(boost::starts_with(v,"offset")
            || boost::starts_with(v,"dword"))
    {
        return false;
    }

    //a number
    char c = v[0];
    if('0'<=c && c<='9')
    {
        //printf("%c\n",c);
        return false;
    }

    //a hex number
    c = v[0];
    if(boost::ends_with(v,"h") &&
            ((c<='9' && c>='0') ||
             ((c>='A' || c>='a')&& (c <='F'|| c<='f') )))
    {
        //std::cout<< boost::ends_with(v,"h");
        //printf(" %c\n",c);
        return false;
    }

    return true;

}

char* getAddr(char* op1)
{
    if(strlen(op1)==0)
        return NULL;
    std::string s = op1;

    if(boost::starts_with(s, "loc_") ||
            boost::starts_with(s, "locret_")||
            boost::starts_with(s, "sub_"))
    {
        std::size_t pos = s.find("_");
        if(pos==std::string::npos)
            return NULL;
        std::string str3 = s.substr(pos+1);
        char *cstr = new char[str3.length() + 1];
        strcpy(cstr, str3.c_str());
        return cstr;
    }
    return NULL;
}


int hashCode(std::string s)
{
    boost::hash<std::string> string_hash;

    return string_hash(s);
}

/**
Read API function name
*/
std::string getAPIFunctionName(std::string func)
{
        std::string Ofunc = myWPDS::split(func, "_").at(0);
        if(Ofunc.size()==0)
        {
            if(boost::starts_with(func,"__imp_"))
            {
                Ofunc = myWPDS::replace(func, "__imp_","");

            }
            else
            {
                Ofunc = func;

            }

        }
        return Ofunc;
}






}


