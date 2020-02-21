/*
 * CommandLine.h
 *
 *  Created on: Mar 22, 2019
 *      Author: knockman47
 */

#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>


using namespace std;

class CommandLine {
public:
    CommandLine(istream &in);    
    char* getCommand() const{ return argv[0]; }        // return a pointer to the command portion of the command-line 
    int getArgCount() const{ return argc; }            // return the number of command-line arguments on the command-line
    char** getArgVector() const;
    char* getArgVector(int i) const{ return argv[i]; } // return a pointer to the ith (zero-relative) command-line 'word
    bool noAmpersand() const;
    ~CommandLine(){ free(argv); }
private:
    int argc=0;
    char **argv;
};



#endif /* COMMANDLINE_H_ */