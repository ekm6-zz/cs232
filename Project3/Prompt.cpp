/* Prompt.cpp defines the methods for the Prompt class
 *The Purpose of this class is to represent the command-line prompt
 * Written by: Justin Baskaran
 */

#ifndef __PROMPT_H__
#define __PROMPT_H__


#include <iostream> 
#include <string>
#include <list>
#include <unistd.h>
#include <pthread.h>
#include<bits/stdc++.h>
#include "Prompt.h"
using namespace std; 

/* Prompt()
 * Purpose:to build a Prompt as the 
 * full path to the working directory
 */
Prompt::Prompt() {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
    }
    
    cout << "\n" << cwd << "$ ";
    getline(cin, response);
}


#endif
