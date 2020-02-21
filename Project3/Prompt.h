/* Prompt.h holds the methods for the Prompt class
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

using namespace std; 

class Prompt{
private:
    string response="";
public:
    Prompt();
    string get() const{return response;}  //an accessor that returns the current value of the Prompt.

};

#endif
