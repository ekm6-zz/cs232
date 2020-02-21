#include <iostream> 
#include <string>
#include <list>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/wait.h>
#include "Path.h"
#include "Prompt.h"
#include "CommandLine.h"
using namespace std; 


int main()
{
  while (true) {
   
    Prompt pt; //= Prompt();
    Path ex; //= Path();
    istringstream str(pt.get()); 
    CommandLine cl = CommandLine(str);
    string argumentCommand = string(cl.getCommand());
    // Move all below code to another Process....
    // cd,exit,pwd

    pid_t pid = fork();
    int status = 0;

    if (pid == 0)
    {
     
      string str12(cl.getCommand());
      if (str12 == "exit"){
        exit(EXIT_SUCCESS);
      } else if (str12 == "cd"){
        string folderPath=" ";
        int returnValue= -1;
        // "/" - / of hard drive
        // "." - current working directory
        // ""  - home directory 
        if (cl.noAmpersand()){
            exit(0);
        }
        if (cl.getArgCount() != 1) {
           // cout << "Length of Arguments: "<< cl.getArgCount() << "\n";
            for (int i=0; i<cl.getArgCount(); i++){
              string stasf12(cl.getArgVector(i));
           //  cout << "Arguments: "<< stasf12 << "\n";
            }
        }
        if (cl.getArgCount()  == 1) {
          returnValue = chdir(getenv("HOME")); 
        } 
        else if (cl.getArgVector(1)[0] == '.') {
          returnValue = chdir(cl.getArgVector(1)); 
        } 
        else if (cl.getArgVector(1)[0] == '/'){
          returnValue = chdir(cl.getArgVector(1)); 
        }
        if (returnValue == 0)
        {
      //  cout << "Sucess" << "\n";
        } else {
          cout << "Failure: "  <<   returnValue << "\n";
        }
      } else {
        int cmd = ex.find(argumentCommand);
        char filePath[150];   
        char *cstr = new char[ex.getDirectory(cmd).length() + 1];
        strcpy(cstr, ex.getDirectory(cmd).c_str());
        char *file2 = cl.getCommand();
        strcpy(filePath,cstr); 
        strcat(filePath,file2); 
        delete [] cstr;
        if (cl.noAmpersand()){
            exit(0);
        }
        char *argv[cl.getArgCount()+1];
        for (int i=0; i<cl.getArgCount();i++){    
          argv[i] = cl.getArgVector(i); 
      
        }
        argv[cl.getArgCount()]  = (char*)0;

        for (int a=0; a<cl.getArgCount();a++){

        }
        
        execve(filePath,argv,NULL); 
        exit(0);

      }
    }
    while ((pid = wait(&status)) > 0); 

  }

}
