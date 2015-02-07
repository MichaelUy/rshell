#include <iostream>
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
#include <cstdlib>
#include <linux/stat.h>
#include <iomanip>
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

void printls(vector<string> filenames, int flags ){
    string displaytime;
    for(int i=0; i < filenames.size();i++){
        struct stat the_goods;
        if(-1== stat(filenames[i].c_str(), &the_goods)){
            perror("error on stat");
            exit(1);
        }
                                                                ////requires iomanip formating
        cout << permissiontags(the_goods) << " ";
        //cout << numlinks << " ";
        struct passwd *pwuid = getpwuid(the_goods.st_uid);
        if(pwuid == NULL){
            perror("error on getpwuid");
        }
        else{
            cout << pwuid->pw_name << " ";
        }
        struct group *grgid = getgrgid(the_goods.st_gid);
        if(grgid == NULL){
            perror("error on getgrgid");
        }
        else{
            cout << grgid->gr_name << " ";
        }
        displaytime = ctime(&the_goods.st_mtime);
        displaytime = displaytime.substr(4,displaytime.length());
        displaytime = displaytime.substr(0,displaytime.length()-9);
        cout << displaytime << " ";
        displaytime="";
        cout << filenames[i] << endl;
    }
}

void printdirs(){                           // handles -R

}


bool isalink(){                                    ////implement

}

int numlink(){                                    ///// implement
    int ret=0;

return ret;
}

int getflags(){

}

int main(int argc,char *argv[]){
    if(argc < 1){                            //check for read error
        cout << "error on arguments"<<endl;
        exit(1);
    }

    vector<string> filenames, dirlist;      //create vectors for filenames and directories
    int flags=0;                            //////flags and dirlist still unused

    char initdirName[]={'.','\0'};          ////////{
    char *dirName = initdirName;
    DIR *dirp = opendir(dirName);       // opendir(paths[i].c_str()); must open path
    if(dirp == NULL){
        perror("error on opendir");
    }
    dirent *direntp;
    while ((direntp = readdir(dirp))){      ///// create directory divided display function
        if(direntp < 0 ){
            perror("error on readdir");
        }
        filenames.push_back(direntp->d_name);
    }

    printls(filenames,flags);
                                        ////////////}
    if(-1==closedir(dirp)){
        perror("error on closedir");
    }
}
