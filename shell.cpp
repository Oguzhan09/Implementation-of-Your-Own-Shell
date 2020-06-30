#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

string getName(){ //this method take user name from the system
    return getenv("USER");
}

vector <string> listdirFunc(){ // this methods print out the contents of the current directory and return vector which hold the name of directories
    vector<string> directions; //create empty vector for all directions
    string s; //create empty string for directions
    struct dirent **namelist;
    int n;
    n = scandir(".",&namelist,NULL,alphasort); // hold number of directories in the current path
    if(n<0){ // if n equal zero, there is no directory in the current path
        perror("scandir");
        exit(EXIT_FAILURE);
    }else{
        while(n--){ // decrease n one by one
            s = namelist[n]->d_name; // assign name of the directory to s
            if(s.substr(0,1) !=  "."){ // if s don't start with "."
                directions.push_back(s); // push the name of directory in the vector
            }
            free(namelist[n]);
        }
        free(namelist);
    }
    return directions; // return directions vector which hold name of directories
}

vector <string> listdirAFunc(){ // this method print out the contents (with hidden files) of the current directory and return vector which hold the name of directories
    vector<string> directions; //create empty vector for all directions
    string s; //create empty string for directions
    struct dirent **namelist;
    int n;
    n = scandir(".",&namelist,NULL,alphasort); // hold number of directories in the current path
    if(n<0){ // if n equal zero, there is no directory in the current path
        perror("scandir");
        exit(EXIT_FAILURE);
    }else{
        while(n--){ // decrease n one by one
            s = namelist[n]->d_name; // assign name of the directory to s
            directions.push_back(s); // push the name of directory in the vector
            free(namelist[n]);
        }
        free(namelist);
    }
    return directions; // return directions vector which hold name of directories
}

string currentPathFunc(){ // this method determine to path and return this path
    char cwd[1024];
    getcwd(cwd, 100);
    return cwd;
}

void printfileFunc(string argument,vector <string> dir){ // this method read the contents of the files and write onto the screen
    fstream file;
    ofstream write;
    string word,filename;
    for(int i =0; i<dir.size(); i++){ // scan the all directories from the vector dir
        if(dir[i].find(argument) != string::npos){ // if the directories contain file which name is argument
            filename = argument; // my filename equal to the argument
        }
    }
    file.open(filename.c_str()); // open the file for reading
    while(file>>word){ // to get all the lines from string
        cout<< word <<endl; // and print onto the screen
    }
}

void printfile2Func(string secondArgument, string argument , vector <string> dir){ // this function copy one file to another file
    fstream file; // file for reading
    ofstream file1; // file for writing
    fstream file2; // file for create
    vector <string> control;
    string word,filename,s, newfilename; // word take input from file and write into to s, filename equal argument and newfilename equal secondargument(arguments is our inputs)
    for(int i =0; i<dir.size(); i++){ // scan the all directories from the vector dir
        if(dir[i].find(argument) != string::npos){ // if the directories contain file which name is argument
            filename = argument; // my filename equal to the argument
        }
    }
    file.open(filename.c_str()); // open the file for reading
    while(file>>word){ // to get all the lines from string
        s = s + word + "\n"; // add word to s
    }
    newfilename = secondArgument; //assign secondArgument to newfilename
    for(int i =0; i<dir.size(); i++){ // in this for loop we check we have file to write or not, if not create new file and copy contents this created file
        if(dir[i].find(secondArgument) == string::npos){ // control all dir vector for we have secondArgument or not
            file2.open(newfilename,ios::out); // if we don't have create
        }
    }
    if(!file2){ // if we dont have any file2
        file1.open(newfilename.c_str()); // open file1
        file1<<s; // write s into the file1
    }else if(file2){ // if we have file2
        file2.open(newfilename.c_str()); // open file2
        file2<<s; // write s into the file2
    }
}

void grepFunc(vector <string> dir,string argument){ // this method control vector dir contains argument or not, it contains print out
    string s = argument.substr(1,argument.length()-2); // Remove quotes from a string
    for(int i =0; i<dir.size(); i++){
        if(dir[i].find(s) != string::npos){ // if elements of the queue contains s
            cout<<dir[i]<<" "; // write element screen
        }
    }
    cout<<endl;
}

void exitFunc(){ // this method terminate the program
    cout<<"The end of the program"<<endl;
    exit(0);
}

void writingQueue(queue <string> commands){ // this method print the elements of the queue
    int i = 1;
    while(!commands.empty()){ // if queue is not empty
        cout<<i << " " <<commands.front()<<endl; // write top of the element of the queue
        i++;
        commands.pop(); // and pop this element
    }
}

string lastWord(string command){ // this method take command (all line) and return the last word which comes after the last space
    string argument;
    int i = command.length()-1;
    while(i!= 0 && !isspace(command[i])){
        --i;
    }
    argument = command.substr(i+1);
    return argument;
}

string secondWord(string command){ // this function return the second element of the input
    istringstream iss(command);
    string word;
    int i = 1;
    while(i <= 2){
        iss >> word;
        i++;
    }
    return  word;
}

int main (int argc, char *argv[]) {
    cout<<"Welcome to my shell"<<endl; // Welcome message to my program
    queue <string> commands; // this will holds all commands until the terminate the program
    string command; // this will hold command which enter by user
    string argument; // this will hold last word from the command
    string secondArgument; // this will hold the second word from the line
    vector <string> dir; // this will hold directories in vector
    cout<< getName() << " >>> "; // print user name to the screen
    getline(cin,command); // get command from user
    while(command != "exit"){  // if command is not equal exit, enter the while
        argument = lastWord(command); // determine the last word of the command
        secondArgument = secondWord(command); // determine the second word of the command
        if(command == "listdir"){ // if command is equal "listdir", print the all directories
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command); // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command); // push the command
            }
            dir = listdirFunc(); // assign listdirFunc() (which return the vector) to vector which name is dir
            for(int i= 0; i<dir.size(); i++){ // print all elements of the dir vector to the screen
                cout<< dir[i] << " ";
            }
            cout<<endl;
        }
        else if(command == "listdir -a"){ // if command is equal "listdir -a", "print the all directories with hidden files"
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command); // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command); // push the command
            }
            dir = listdirAFunc(); // assign listdirAFunc() (which return the vector) to vector which name is dir
            for(int i= 0; i<dir.size(); i++){ // print all elements of the dir vector to the screen
                cout<< dir[i] << " ";
            }
            cout<<endl;
        }
        else if(command == "currentpath"){ // if the command equal "currentpath", print the current working directory
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command);  // push command to queue
            }else{  // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command);  // push the command
            }
            cout<<currentPathFunc()<<endl;
        }
        else if(command == "printfile " + argument){ // if the command equal "printfile + argument", print the current working directory
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command); // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command);  // push the command
            }
            dir = listdirAFunc(); // assign listdirAFunc() (which return the vector) to vector which name is dir
            printfileFunc(argument,dir); // go to this function and print contents of the file
        }
        else if(command == "printfile " + secondArgument + " > "+ argument){
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command); // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command); // push the command
            }
            dir = listdirAFunc(); // assign listdirAFunc() (which return the vector) to vector which name is dir
            printfile2Func(argument,secondArgument,dir); // go to this function and copy contents of the file to another file
        }
        else if(command == "footprint"){ // if command equal "footprint" print to maximum 15 commands that are executed before
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command);  // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command);  // push the command
            }
            writingQueue(commands); // go to writingQueue function and print all elements of the commands queue
        }
        else if(command == ("listdir | grep " + argument)){ // if command equal "listdir | grep 'argument'"
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command);  // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command);  // push the command
            }
            dir = listdirFunc(); // assign listdirFunc() (which return the vector) to vector which name is dir
            grepFunc(dir,argument); // print directories which contains argument
        }
        else if(command == ("listdir -a | grep " + argument)){
            if(commands.size() < 15 ){ // if queue size less than 15
                commands.push(command);  // push command to queue
            }else{ // if queue size more than 15
                commands.pop(); // pop one element from queue
                commands.push(command);  // push the command
            }
            dir = listdirAFunc(); // assign listdirAFunc() (which return the vector) to vector which name is dir
            grepFunc(dir,argument); // print directories which contains argument
        }else{
            cout<< "You entered an incorrect or missing command, please try again"<<endl;
        }
        cout<< getName() << " >>> "; //  print user name to the screen
        getline(cin,command); // get command from user
    }
    if(command == "exit"){ // if the command equal "exit", go to exitFunc()
        exitFunc();
    }
    return 0;
}