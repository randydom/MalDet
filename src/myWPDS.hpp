#ifndef MYWPDS_HPP_INCLUDED
#define MYWPDS_HPP_INCLUDED
#include"mycfg.hpp"

#include <chrono>
#include <ctime>
namespace myWPDS
{

static std::chrono::time_point<std::chrono::system_clock> startTime;
static std::string path ="";//"H:\\workspace\\wpds\\samples\\";
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64)
static std::string temp = "temp\\";
#else
        static std::string temp = "temp/";
#endif

static std::string apiFile = "msdn_data_nn";

static std::string pdsfile=temp+"outputPDS.txt";
static std::string poststarfile=temp+"poststar";
static std::string outputFunc=temp+"Function.txt";
static std::string outputCFG=temp+"CFG.txt";
static std::string outputNameDomain=temp+"nameDomain.txt";

static std::string examfile;

static int CallDepth = 50;



///marked is a collection of possible states of the program. It is used to mark the visited states.
static std::set<int> marked;
static std::map<long, boost::any> mCFG;
static std::map<std::string, boost::any> mFunc;


/**/
typedef struct apiType
{
    std::string name;
    std::string desc;
    std::string ret;
    int nArgs;
}apiType;

typedef struct funcType
{
    std::string name;
    int nArgs;
    long addr;
    bool api;
}funcType;

typedef std::map<std::string, funcType*> mFuncType;


static  mFuncType mfapi;

/**/
typedef std::set<std::string> stringSet;

typedef std::map<std::string, stringSet*> varType;

typedef struct ruleSet
{
    stringSet s;
    varType var;
}ruleSet;


typedef std::map<std::string,ruleSet*> tranType;

typedef std::map<std::string,tranType*> ruleType;

static ruleType mTrans;

typedef struct pdsRule
{
    std::string n0,n1;
    std::string s0,s1,s2;
}pdsRule;

typedef std::set<pdsRule*> pdsRuleSet;

typedef std::map<std::string,pdsRuleSet*>  pdsType;

/*pds contains the left address and all rules go  from this left address*/
static pdsType Lpds;
/*pds contains the right address and all address go to this right address*/
//static tranType Rpds;


typedef struct edgeType
{
    std::string e0,e1;
    int f;
    stringSet* var;
}edgeType;

typedef struct nodeType
{
    std::string n;
    stringSet* var;
    int f;
}nodeType;

typedef std::map<std::string, nodeType*> gNodeType;

typedef std::map<std::string, edgeType*> gEdgeType;


void Run(std::string name);

/// FUNCTIONS ///
void example();
void example2();
void example3();
void example4(std::string name,int opt,int depth,bool abstractG);
void computeTheta(std::string filename);
std::string createRule(std::string addr,std::string sym0,std::string next, std::string sym1,std::string sym2, int i0,int i1);
stringSet* &computeDep(std::string reg,std::string addr, stringSet* &ret);
ruleSet* &copyS0toS1(ruleSet* &sSet0, ruleSet* & sSet1,std::string skip, bool&comp);
void computeDEPGraph(std::string fpds,std::string fn);
void computeDEPGraph(std::string fn,gEdgeType & edge,gNodeType& api,bool abstractG);

/*Handle states in Jakstab*/
void readJakstabState(std::string filename);
}



#endif // MYWPDS_HPP_INCLUDED
