#include <boost/any.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <exception>
#include <thread>
#include <mutex>


#include <chrono>
#include <ctime>
#include <pthread.h>

#include "myWPDS.hpp"
#include"myUtil.hpp"


using namespace std;

    string descfile;
    string testfile;
    string suffix ="Eapi";
    int opt=0; //default value 0:Eapi, 1:Api, 2: Eapi and Api
    int depth =50;
    int cleanopt=1;
    bool abstractG=false;
    string N="15",F="3",S="1",W="2";

inline bool exists_test (const std::string& name) {
   if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void usage(char *myname)
{
  char *progname = myname;
  char *base;
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
    base  = strrchr(progname,'\\');
  #else
    base  = strrchr(progname,'/');
  #endif
  if (base) progname = base+1;


  fprintf(stderr,
    "\n%s -- A Tool for Malware Detection\n\n"

    "Usage: %s <Command> [options] [<TestFile>] [<ListFiles>]\n\n"

    "    Commands:\n"
    "      Train  Compute the malicious API graphs from executables in <ListFiles> \n"
    "        \t   Usage: %s Train [options] <ListFiles> \n\n"
    "      Test   Check an executable file (<TestFile>) \n"
    "        \t   Usage: %s Test [options] <TestFile> <ListFiles> \n\n"
    //"      Graph  Compute the graphs for executables in <ListFiles>. \n"
    //"        \t   Usage: %s Graph [options] <ListFiles> \n\n"

    "    Options:\n"
    "    -g<n>  specify the kind of graph to compute \n"
    "       \t        n=0 denotes Extended API call graph (default), \n"
    "       \t        n=1 denotes API call graph, \n"
    //"       \t        n=2 denotes both graphs. This option is only used for command Graph. \n"
//    "    -d<n>  specify the max depth of traverse in CFG (default n=10). \n"
    //"    -r     compute Abstract API call graph instead of API call graph. \n\n"
    "    -N<n>  specify the number of highest terms in the malicious API graph. \n"
    "    -F<f>  specify the type of the function used in the term weighting scheme. \n"
    "       \t        f=0 denotes function F1 (a linear function), \n"
    "       \t        f=1 denotes function F2 (a rational function), \n"
    "       \t        f=2 denotes function F3 (a logarithmic function), \n"
    "       \t        f=2 denotes function F4 (a sigmoid function). \n"
    "    -W<w>  specify the Equation used in the term weighting scheme. \n"
    "       \t        w=1 denotes Rocchio Equation, \n"
    "       \t        w=2 denotes Ratio Equation. \n"
    "    -S<s>  specify the strategy (s=1,2,3) to compute graphs. \n"
     ,
    progname, progname,progname,progname,progname);

  /*fprintf(stderr,
    "\nCopyright (c) \n"
      "See Copying for legal information.\n"
    "\nVersion 1.0.0 (31.01.2018)\n\n");
*/
fprintf(stderr,
    "\nVersion 1.0.0 (31.01.2018)\n\n");
  exit(1);
}


mutex m;
bool tquit=false;
void* ExcuteSystem(char* cmd )
{
   //std::cout << "\tExecute: "<< cmd << "\n";
   system(cmd);
   m.lock();
   tquit=true;
   m.unlock();
}

void preexecute(string filename)
{

    std::string CMD;

        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
        CMD="Jakstab\\jakstab -s -h -v 0  --procedures 2 -m "+filename;
        #else
        CMD="./Jakstab/jakstab -s -h -v 0 --no-graphs --procedures 2 -m "+filename;
        #endif
        CMD+=" > " + filename;
        CMD+="_States.out";

        tquit=false;
        pthread_t t;
        pthread_create(&t,NULL,ExcuteSystem,CMD.c_str());
        /*thread t(ExcuteSystem,CMD);*/

        std::chrono::time_point<std::chrono::system_clock> startT, endT;
        startT = std::chrono::system_clock::now();
        endT = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = endT-startT;
        while(!tquit && elapsed_seconds.count() <60)
        {
            this_thread::sleep_for(std::chrono::seconds(5));
             endT = std::chrono::system_clock::now();
            elapsed_seconds = endT-startT;
            //std::cout << elapsed_seconds.count()<<"\n";
        }
        if(!tquit)
        if(pthread_cancel(t))
        {
            std::cout << "Cancel Jakstab!!\n";
        }

        //ExcuteSystem(CMD.c_str());

        string cmd;
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
        cmd="IDA65\\idaq.exe -B "+filename;
        #else
        cmd="./IDA/idal -B "+filename;
        #endif
        ExcuteSystem(cmd.c_str());

}

std::string upxPacked(std::string filename)
{
    std::string CMD;
    std::string fname= filename +"_packer.out";
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
        CMD = "python PEiD\\packerid.py -D PEiD\\userdb.txt "+ filename;
        #else
        CMD = "python ./PEiD/packerid.py -D ./PEiD/userdb.txt "+filename;
        #endif
    CMD+=" > " + fname;
    ExcuteSystem(CMD.c_str());
    std::fstream infile;
    infile.open(fname, std::fstream::in);
    if(infile==NULL)
        std::cout << "File not found\n";
    //assert(infile);
    std::string line;
    std::getline(infile, line);
    if(boost::algorithm::contains(line,"UPX"))
    {
        fname = filename;
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
        CMD = "PEiD\\unpacker\\upx.exe -d -o"+fname +" "+filename;
        #else
        CMD = "./PEiD/unpacker/upx_linux/upx -d -o"+fname +" "+filename;
        #endif
        ExcuteSystem(CMD.c_str());
        preexecute(fname);
        std::remove((fname).c_str());
        return fname;
    }
    infile.close();
    std::remove((filename +"_packer.out").c_str());
    preexecute(filename);
    return filename;
}



void clean(std::string filename)
{
    std::remove((filename+"_Func.out").c_str());
    std::remove((filename+"_statements.out").c_str());
    std::remove((filename+"_States.out").c_str());
    std::remove((filename+"_API.out").c_str());



    std::string filename1 = filename.substr(0,filename.find_last_of("."));

    std::remove((filename1+"_callgraph.dot").c_str());
    std::remove((filename1+"_cfa.dot").c_str());
    std::remove((filename1+"_jak.asm").c_str());
    std::remove((filename1+".idb").c_str());
    std::remove((filename1+".asm").c_str());
}

int run( std::string filename)
{

    //cout << "Let us start :-)!" << endl;


    try
    {



        //filename = "D:\\workspace\\PCDataset\\benware\\aria2c.exe";
        //opt = boost::lexical_cast<int>(argv[1]);

        //filename ="E:\\netsetup.exe.zp";

        //preexecute(filename);
        filename = upxPacked(filename);

        myWPDS::example4(filename,opt,depth,abstractG);


    }
    catch(runtime_error& e1 )
    {
        cout << "runtime exception: " << e1.what() << endl;

        //exit(0);

        //throw;
    }
    catch(exception& e )
    {
        cout << "Standard exception: " << e.what() << endl;
        //exit(0);
        //throw;

    }

    if(cleanopt!=0)
        clean(filename);
    return 0;
}

void ReadDescription(string filename){
    std::fstream infile;
    infile.open(filename, std::fstream::in);
    if(infile==NULL)
        std::cout << "File not found\n";
    //assert(infile);
    std::string line;
    while(std::getline(infile, line))
    {
        if(boost::algorithm::starts_with(line,"@"))
            continue;
        std::string cname = line+"_"+suffix+"Node";
        //std::cout << cname <<"\n";
        if(!exists_test(cname))run(line);
    }
}

void trainRun()
{
    std::cout<< "Waiting...\n";
    ReadDescription(descfile);


    std::string cmd;
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__CYGWIN__)
    cmd = "md specification";
    #else
    cmd = "mkdir specification";
    #endif
    ExcuteSystem(cmd.c_str());

    cmd = descfile;
    cmd = "java -jar PCTFIDFTool.jar train "+cmd;
    cmd+=" specification "+suffix;
    cmd+= " "+N;
    cmd+= " "+W;
    cmd+= " "+F;
    cmd+= " "+S;
    ExcuteSystem(cmd.c_str());
}



void testRun()
{
    std::cout<< "Checking...\n";
    std::string cmd;
    std::string filename = testfile;
    filename+=+"_"+suffix+"Node";

    if(!exists_test(filename))run(testfile);
    cmd = "java -jar PCTFIDFTool.jar predict "+descfile +" "+ testfile;
    cmd+=" specification "+ suffix;
    cmd+= " "+N;
    cmd+= " "+W;
    cmd+= " "+F;
    cmd+= " "+S;
    std::cout << testfile <<"\t";
    ExcuteSystem(cmd.c_str());
}

int main(int argc, char *argv[])
{
    //usage(argv[0]);
     if (argc <2)
    {
        usage(argv[0]);
        return 0;
    }


    /* traverse arguments, get filenames */
	for (int i = 2; i < argc-1; i++)
	{
	  if (*argv[i] == '-')
	  {
			while (*++argv[i])
		    switch (*argv[i])
		    {
		        //select the graph
            case 'g':
                opt = *(argv[i]+1)-'0';
                break;
            case 'd':
                depth = boost::lexical_cast<int>((argv[i]+1));
                //std::cout << depth << "\n";
                break;
            case 'c':
                cleanopt = *(argv[i]+1)-'0';
                break;
            case 'r':
                abstractG=true;
                break;
            case 'N':
                N =(char*)(argv[i]+1);
                break;
            case 'F':
                F =(char*)(argv[i]+1);
                break;
            case 'W':
                W =(char*)(argv[i]+1);
                break;
            case 'S':
                S =(char*)(argv[i]+1);
                break;
		    }
	  }
	}
	if(opt==0)suffix=abstractG?"AEapi":"Eapi";
	if(opt==1)suffix=abstractG?"Aapi":"Api";

	testfile = argv[argc-2];
	descfile = argv[argc-1];

        std::chrono::time_point<std::chrono::system_clock> startT, endT;
        startT = std::chrono::system_clock::now();

	if(boost::algorithm::equals(argv[1],"Train"))
    trainRun();
    if(boost::algorithm::equals(argv[1],"Test"))
    testRun();
    if(boost::algorithm::equals(argv[1],"Graph"))
    run(descfile);

        endT = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = endT-startT;
        std::time_t end_time = std::chrono::system_clock::to_time_t(endT);

        std::cout << "Finished computation at " << std::ctime(&end_time)
                 << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}




