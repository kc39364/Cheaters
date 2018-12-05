#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <queue>
#include <string>
#include <iostream>   // Provides cout and cin
#include <fstream>   // For file access

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

vector<string> getNWordSequence(string dir, vector<string> fileNames, int n);

//
//
//
//
//
//
//
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Invalid program call!" << endl;
        exit(-1);
    }

    string dir = string(argv[1]);   // sm_doc_set, med_doc_set, or big_doc_set
    vector<string> fileNames = vector<string>();

    getdir(dir,fileNames);   // store all txt file names in files vector

    // for (unsigned int i = 0;i < fileNames.size();i++) {   // print out all txt file names in the directory
    //     cout << i << fileNames[i] << endl;
    // }

    vector<string> keys = getNWordSequence(dir, fileNames, 5);
    
    // print all possible n-word sequences
    // for(vector<string>::iterator iter = keys.begin(); iter != keys.end(); iter++){
    //     cout << (*iter) << endl;
    // }
    cout << keys.size() << endl;

    return 0;
}
//
//
//
//
//
//
//

vector<string> getNWordSequence(string dir, vector<string> fileNames, int n){
    vector<string> sequences;
    
    for(int fileNum = 2; fileNum < fileNames.size(); fileNum++){   // fileNum = 2 to skip to txt files
        ifstream infile;
        infile.open(dir + "/" + fileNames[fileNum]);   // read one file at a time

        queue<string> nWords;

        string word;
        while(infile >> word){
            nWords.push(word);
            if(nWords.size() == n){
                queue<string> tempWords = nWords;

                string sequence;
                while(!tempWords.empty()){
                    sequence += tempWords.front();
                    sequence += " ";
                    tempWords.pop();
                }

                sequences.push_back(sequence);
                nWords.pop();
            }
        }

        infile.close();
    }

    return sequences;
}
