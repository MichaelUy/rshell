#include <iostream>

#include <deque>
#include <time.h>
#include <pwd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc,char *argv[]){

    char initdirName[]={'.'};
    char *dirName = initdirName;
    DIR *dirp = opendir(dirName);
    dirent *direntp;
    while ((direntp = readdir(dirp))){
        cout << direntp->d_name << endl;  // use stat here to find attributes of file
    }
    closedir(dirp);
}
