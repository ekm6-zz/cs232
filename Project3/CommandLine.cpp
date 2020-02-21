/* CommandLine.cpp defines the methods for the CommandLine class
 *The Purpose of this class is to read a command-line
 * Created on: Mar 22, 2019
 * Written by: Enoch Mweisgwa
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "CommandLine.h"


using namespace std;

/* runCommandLine
* @param: istream in
* Purpose: collects user 
* command and initializes argc and argv
*/
CommandLine::CommandLine(istream &in){

    argv = (char**)calloc(10+1, sizeof(char*));
    
    ostringstream oss;
    oss << in.rdbuf();
    string Arguments = oss.str();

    char *token; 

    char* cstr = strcpy(new char[Arguments.length() + 1], Arguments.c_str());

    int i=0;
    token = strtok_r(cstr, " ", &cstr);
    while (token != NULL)
    {
        argv[i] = token;
        i = i +1; 
        argc = argc +1;
        token = strtok_r(NULL, " \n", &cstr);
    }
        
    argv[10] = (char*)0;
}

/* getArgVector()
* @return: a pointer to a char* array
* Purpose: convert the command into and 
* array of which each entry of which points 
* to one 'word' of the command-line
*/
char** CommandLine::getArgVector() const{
    char **returnValue;
    for (int i = 1; i < getArgCount(); i++) {
        returnValue[i] = argv[i];
    }
    return returnValue;
}

/* noAmpersand()
* @return: boolean value 
* Purpose: searches the command '&'
* and returns true if and only if no 
* ampersand was given on the command-line 
*/
bool CommandLine::noAmpersand() const{
 bool condition = false;
 string arg;
 for (int i = 1; i < argc; i++) {
  arg = argv[i];
  if (arg == "&") {
   condition  = true;
  }
 }
 return condition;
}




#endif /* COMMANDLINE_H_ */