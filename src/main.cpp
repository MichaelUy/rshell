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
#include <vector>
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
    char connectorparsed[32000];
	int tokenindex=0;
	char* savedTokens[32000];
    char* toke[32000];
    vector<char> myvector;
    while(1){
    myvector.clear();
    tokenindex = 0;
   	cout<<user<<"@"<<host<< "$ ";
	getline(cin,str);		// get input at str
	strcpy(cmd,str.c_str());	// get c string of str
   	strcpy(connectorparsed,str.c_str());
    for(int i=0;cmd[i]!='\0';i++){

        if( cmd[i]==';' ){
            myvector.push_back(' ');
            myvector.push_back(cmd[i]);
            myvector.push_back(' ');

        }
        else if( cmd[i]=='&'&& cmd[i+1]=='&' ){
            myvector.push_back(' ');
            myvector.push_back(cmd[i]);
            myvector.push_back(cmd[i]);
            myvector.push_back(' ');
            i++;
        }
        else if( cmd[i]=='|'&& cmd[i+1]=='|'){
            myvector.push_back(' ');
            myvector.push_back(cmd[i]);
            myvector.push_back(cmd[i]);
            myvector.push_back(' ');
            i++;
        }
        else{
            myvector.push_back(cmd[i]);
         }
    }

    for(int i=0;i<myvector.size();i++){
        connectorparsed[i]=myvector.at(i);
        //cout<< connectorparsed[i];
    }
    //cout<< endl;


    // char* tokens= strtok(cmd," ");
    char* tokens= strtok(connectorparsed," ");


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
    /*
    for(int i = 0; i < tokenindex; i++){
        cout << "savedTokens[ " << i << " ] = " << savedTokens[i] << endl;

    }
    */
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
