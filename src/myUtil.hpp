#ifndef MYUTIL_HPP_INCLUDED
#define MYUTIL_HPP_INCLUDED

#include <boost/any.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string/replace.hpp>


#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include<stdlib.h>
//#include <vector>


namespace myWPDS
{
    ///util ///
char* decimalToHex(long number);
long hexToDecimal(const char* s);
std::string replace(std::string input, std::string seach, std::string r);
std::string removeSpaces(std::string input);
std::string removeChar(std::string input, char r);
std::vector<std::string> split(std::string s, std::string c);
bool isVar(char* v);

void fprint_map(std::map<long, boost::any> s,std::map<int,std::string> nameDomain,char* fname);
void fprint_map(std::map<std::string, boost::any> mFunc,char* fname);
void fprint_set(std::set<std::string> s,char* fname);
void print_varSet(std::map<long, boost::any> m);
void print_var_t(void* v);
std::string var2String(void* v);
char* duplicate(const char* s);
char* getAddr(char* op1);
int hashCode(std::string s);


std::string getAPIFunctionName(std::string func);

}


//char* strdup(const char* s){return Strdup(s);};

#endif // MYUTIL_HPP_INCLUDED
