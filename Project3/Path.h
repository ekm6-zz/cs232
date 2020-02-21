/* Path.h holds the methods for the Path class
 *The Purpose of this class is to represent the directories 
 in which the shell searches for executable program
 * Written by: Justin Baskaran
 */
#include <iostream> 
#include <string>
#include <list>
#include <vector>
#include <dirent.h>


using namespace std; 

class Path{
    private:
    vector <string> dir = vector <string> ();

    public:
    Path();

    int find(const string& program) const;
    string getDirectory(int i) const { return dir.at(i)+"/";}   // return the name of the directory whose index is i

};
