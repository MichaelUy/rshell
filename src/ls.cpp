#include <iostream>
#include <string.h>
#include <vector>
#include <deque>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/stat.h>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <stack>
using namespace std;

string permissiontags (struct stat &the_goods){
    string ret = "----------";                               // create a 10 '-' string
    switch (the_goods.st_mode & S_IFMT){                       // first '-' goes to file type
    case S_IFBLK:    ret[0] = 'b';     break;
    case S_IFCHR:    ret[0] = 'c';     break;
    case S_IFDIR:    ret[0] = 'd';     break;
    case S_IFIFO:    ret[0] = 'p';     break;
    case S_IFLNK:    ret[0] = 'l';     break;
    case S_IFREG:    ret[0] = '-';     break;
    case S_IFSOCK:   ret[0] = 's';     break;
    default:         ret[0] = '-';     break;
    }
                                                            // other 9 goes to permissions
    if(the_goods.st_mode & S_IRUSR) ret[1] = 'r';
    if(the_goods.st_mode & S_IWUSR) ret[2] = 'w';
    if(the_goods.st_mode & S_IXUSR) ret[3] = 'x';
    if(the_goods.st_mode & S_IRGRP) ret[4] = 'r';
    if(the_goods.st_mode & S_IWGRP) ret[5] = 'w';
    if(the_goods.st_mode & S_IXGRP) ret[6] = 'x';
    if(the_goods.st_mode & S_IROTH) ret[7] = 'r';
    if(the_goods.st_mode & S_IWOTH) ret[8] = 'w';
    if(the_goods.st_mode & S_IXOTH) ret[9] = 'x';
                                                            //// numlinks needs to be handled
    return ret;
}

int totalblocks(vector<string> filenames, string currpath){
    int ret = 0;
    for(size_t i=0; i < filenames.size();i++){
       struct stat the_goods;
       if(-1 == stat((currpath + "/" + filenames[i]).c_str(), &the_goods)){
           perror("error on totalblocks stat");
           exit(1);
        }
        ret+= the_goods.st_blocks;
    }
    return ret;
}

void printls(vector<string> &filenames,bool flaga,bool flagl,bool flagr, string currpath){
    string dirc = "\033[1;34m";     //blue
    string exec = "\033[0;32m";    //green
    string filec = "\033[m";        // nothing
    string linkc = "\033[1;36m";    // cyan
    string socketc = "\033[1;35m";  //magenta
    string pipec = "\033[0;40;33m"; //
    string blockc = "\033[1;33;40m";   //bold  yellow black bgd
    string hidden = ";47m";   // white background   -unfinished

    string displaytime;
    string color="";                 // default color = green


    if(flagl){
         cout << "total " << totalblocks(filenames,currpath)/2;
         if(!filenames.empty() ){
            cout << endl;
        }
    }
    for(size_t i=0; i < filenames.size();i++){
        struct stat the_goods;
            if(-1== stat((currpath + "/" + filenames[i]).c_str(), &the_goods)){
                perror("error on stat");
                exit(1);
            }
        if(flagl){
            cout << permissiontags(the_goods) << " ";
            cout << the_goods.st_nlink << " ";
            struct passwd *pwuid = getpwuid(the_goods.st_uid);
            if(pwuid == NULL){
                perror("error on getpwuid");
                exit(1);
            }
            else{
                cout << pwuid->pw_name << " ";
            }
            struct group *grgid = getgrgid(the_goods.st_gid);
            if(grgid == NULL){
                perror("error on getgrgid");
                exit(1);
            }
            else{
                cout << grgid->gr_name << " ";
            }
            cout << setw(6)<< the_goods.st_size << " ";
            displaytime = ctime(&the_goods.st_mtime);
            displaytime = displaytime.substr(4,displaytime.length());
            displaytime = displaytime.substr(0,displaytime.length()-9);
            cout << displaytime << " ";
            displaytime="";
        }


    switch (the_goods.st_mode & S_IFMT){        // SUPPORTS:
    case S_IFBLK:    color = blockc;    break;  // BLOCK DEVICES
    case S_IFCHR:    color = blockc;    break;  // CHARACTER DRIVERS
    case S_IFDIR:    color = dirc;      break;  // DIRECTORIES
    case S_IFIFO:    color = pipec;     break;  // PIPES
    case S_IFLNK:    color = linkc;     break;  // LINKS
    case S_IFREG:    color = filec;     break;  // REGULAR NON- EXE FILES
    case S_IXUSR:    color = exec;      break;  // EXE FILES
    case S_IFSOCK:   color = socketc;   break;  // SOCKETS
    default:         color = filec;     break;
    }
    if(filenames[i][0] == '.'){                 // COMBINABLE HIDDEN FILES!
        color= color.substr(0,color.size()-1) + hidden;
    }
        cout << color << filenames[i] <<"\033[m" <<" " ;
        if(flagl && i != filenames.size()-1){
            cout<< endl;
        }
    }
    cout<< endl;
}




bool nocasenodot(string f,string s){

    string first=f;
    string second=s;
    for(size_t i = 0; i < first.size(); i++){
        first[i] = tolower(first[i]);
    }
    if(first[0]=='.' && (first[1] != '.' || first[1] != '\0')){
        first.erase(first.begin());
    }
    for(size_t i = 0; i < second.size(); i++){
        second[i] = tolower(second[i]);
    }
    if(second[0]=='.' && (second[1] != '.' || second[1] != '\0')){
        second.erase(second.begin());
    }

    return first < second;
}

void getflags(const int argc,char *argv[]
    ,bool &flaga,bool &flagl,bool &flagr ,stack<string> &dirlist){
    size_t argcount = argc;
    for(size_t i=argcount-1;i!=0;i--){
        if(argv[i][0]=='-'){
            if(argv[i][1]=='\0'){
                perror("ls: cannot access -: ");
                exit(1);
            }
            for(int j =1;argv[i][j]!='\0';j++){
                if(argv[i][j] == 'a'){
                    flaga=true;
                    continue;
                }
               else if(argv[i][j] == 'l'){
                    flagl=true;
                    continue;
                }
                else if(argv[i][j] == 'R'){
                    flagr=true;
                    continue;
                }
                else{
                    stringstream str;
                    str << "ls: cannot run invalid flag '";
                    char inval= (argv[i][j]);
                    str << inval << '\'';
                    string s= str.str() ;
                    cerr << s << endl;
                    exit(1);
                }


            }
        }
        // if it not a flag then it should be a directory
        else{
            if(argv[i] )
            dirlist.push(argv[i]);

        }

    }
}




void  recurse(stack<string> &dirlist, vector<string> &filenames, string currpath ){
              if(filenames.size()>0){
                for(size_t b = filenames.size()-1  ; (b+1)!=0  ;b--){
                    struct stat the_goods;
                    //cout <<"b: " << b << endl;
                    if(-1== stat((currpath + "/" + filenames[b]).c_str(), &the_goods)){
                        perror("error on main:stat");
                        exit(1);
                    }
                    if(the_goods.st_mode & S_IFDIR &&
                         !(filenames[b][0]=='.' &&
                         (filenames[b][1]=='\0'||filenames[b][1]=='.'))){

                        //cout <<"PUSHED: "<< filenames[b] << endl;;
                        dirlist.push((currpath + "/" + filenames[b]));
                    }

                }
        }


//    return ret;
}

int main(int argc,char *argv[]){
    if(argc < 1){                            //check for read error
        cout << "error on arguments"<<endl;
        exit(1);
    }

    vector<string> filenames;
    stack<string> dirlist;      //create vectors for filenames and a stack for directories
    bool flaga=false;
    bool flagl=false;
    bool flagr=false;

    getflags(argc,argv,flaga,flagl,flagr,dirlist);  // get flag boos and fill dirlist

    if( dirlist.empty()){                      // if no directories set to local
        dirlist.push(".");
    }
    string currpath ="";
    while(!dirlist.empty()){
        currpath = dirlist.top();
        //cout<< currpath << endl;
        if(dirlist.size()>1 || flagr ){
            cout<< dirlist.top()<<":"<<endl;
        }
        DIR *dirp = opendir(dirlist.top().c_str());       // opendir(paths[i].c_str()); must open path
        if(dirp == NULL){
            perror("error on opendir");

            exit(1);
        }
        dirent *direntp;
        while ((direntp = readdir(dirp))){      ///// create directory divided display function
            if(direntp < 0 ){
                perror("error on readdir");

            }
            if(direntp->d_name[0]  == '.' && !(flaga) ){
                //do nothing
            }
            else{
                filenames.push_back(direntp->d_name);
            }
        }

        // sort the filenames
        sort(filenames.begin(),filenames.end(), nocasenodot);
        printls(filenames,flaga,flagl,flagr, currpath);
        dirlist.pop();
                                    // remove curr directory
        if(flagr){
           recurse(dirlist,filenames,currpath);

           if(!dirlist.empty()){
                 cout << endl;
           }
        //bool ret = false;
           // cout<<" filenames size: " << filenames.size() << endl;
           /*
            if(filenames.size()>0){

                for(size_t b = filenames.size()-1  ; b!=0  ;b--){
                    struct stat the_goods;
                    //cout <<"b: " << b << endl;
                    if(-1== stat((currpath + "/" + filenames[b]).c_str(), &the_goods)){
                        perror("error on main:stat");
                        exit(1);
                    }
                    if(the_goods.st_mode & S_IFDIR &&
                         !(filenames[b][0]=='.' &&
                         (filenames[b][1]=='\0'||filenames[b][1]=='.'))){

                       // ret=true;
                        dirlist.push((currpath + "/" + filenames[b]));
                    }

                }
        }
*/







         //   cout << endl;
        }

        filenames.clear();      //empty the file names

        if(-1==closedir(dirp)){
            perror("error on closedir");
            exit(1);
        }
     }

    }
