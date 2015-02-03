#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

using namespace std;

/*
 *  * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
 *   * that there is no error checking on these functions.  You MUST add error 
 *    * checking yourself.
 *     */

int main(int argc,char *argv[])
{
	char *dirName;   
	char dot[]=".";
	if(argv[1]!=NULL)
		dirName= argv[1];
	else   dirName =dot ;
   
	 DIR *dirp = opendir(dirName);
   	if(dirp==NULL){
	perror("error on opendir");
	}
	 dirent *direntp;
	struct stat status;
    while ((direntp = readdir(dirp)))
        cout << direntp->d_name << endl;  // use stat here to find attributes of file
	if(-1==	stat(drirentp->d_name,&status)){
		perror(" stat error");

	 closedir(dirp);
}


