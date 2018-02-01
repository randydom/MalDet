#ifndef MYCFG_HPP_INCLUDED
#define MYCFG_HPP_INCLUDED
#include"myUtil.hpp"

#include <boost/any.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <set>
#include <string>
#include <stack>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>


namespace myWPDS
{
static std::map<int, std::string> nameDomain;
void print_nameDomain(std::string filename);
std::map<int, std::string> NAMEDOMAIN();

///Entry points type
typedef struct entryPoint
{
    long e;
    struct entryPoint* next;
}entryPoint;

/// Node structure
typedef struct node
{
    char* inst;
    int r1;
    long v1;
    int r2;
    long v2;
    long next1=-1;
    long next2=-1;
    bool api=false; //this node contains a API function name
    //long eP; //entry point of the procedure which contains this node
    //long xP; //exit point of the procedure which contains this node
    bool reached=false;
    void* varSet;   //store all variables at this node defined in struct var_t
    char* comm; //comment in IDA
} node;


/*Handle states in Jakstab*/
static std::map<long,std::map<std::string, std::set<std::string>>> mStates;


///Entry points type
entryPoint* addEntryPoint(entryPoint* s,long v);

///node
node* createNode(char*inst,char* r1, int v1, char* r2, int v2);

/// CFG construction
node* getValue(std::map<long, boost::any> m, long v);
char* getAddr(char* op1);
bool contain(std::set<std::string> m, std::string v);
std::map<long, boost::any> readNode(char* fname,entryPoint** start);
std::map<long, boost::any> readEdge( std::map<long, boost::any> m,char* fname);
std::map<long, boost::any> createCFG(char* fname, entryPoint** start);



}

#endif // MYCFG_HPP_INCLUDED
