#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <cstring>
using namespace std;

char exitS[]="exit";
char exitB[]="Exit";


int main(int arc, char **argv){

    string user;
    char host[3200];
    user= getlogin();
    gethostname(host,3200);

	string str="";
	char cmd[320000];

	int tokenindex=0;
	char* savedTokens[32000];
    char* toke[32000];
    while(1){

    tokenindex = 0;
   	cout<<user<<"@"<<host<< "$ ";
	getline(cin,str);		// get input at str
	strcpy(cmd,str.c_str());	// get c string of str
	char* tokens= strtok(cmd," ");
    cout << cmd<<endl;
 /*
    for(int i=0;i<tokens.size();i++){
        if( tokens[i]==';' )
            token[i]

    }

*/
	while(tokens!= NULL){
		savedTokens[tokenindex]= strdup(tokens);
		tokenindex++;
			tokens=strtok(NULL," ");
		}                   // done tokenizing
        savedTokens[tokenindex]=NULL;
	if(strcmp(exitS,savedTokens[0])==0||strcmp(exitB,savedTokens[0])==0){
	return 0;
	}


    //testing

       //testing

    int pid=fork();
	if(pid==-1){
		perror("error in fork");
        exit(1);
	}
	else if (pid ==0) { //in child process
		if(-1==execvp(savedTokens[0],savedTokens)){
            perror("error in execvp");
            exit(1);
    }
     for(int i=0;i<tokenindex;i++){
     cout<< "savedtoken["<<i<<"]="<< savedTokens[i] << endl;
    }


       exit(1);
	}
	else if (pid>0) {
        if(-1 == wait(0)) //wait for the child process to finish
        {
            perror("error in wait");
	        // exit(1);
        }

    }
    }
}
