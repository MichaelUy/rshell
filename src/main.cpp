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
char directin[]={'<','\0'};
char directout[]={'>','\0'};
char apdirectout[]={'>','>','\0'};
char piper[]={'|','\0'};

char andd[]={'&','&','\0'};
char orr[]={'|','|','\0'};
char semi[]={';','\0'};
bool isin(char** savedTokens,string search ){
    bool ret = false;
    for(size_t i=0;savedTokens[i]!=NULL;i++){
      if(strcmp(savedTokens[i],search.c_str())==0){
            ret=true;
        }
        if(strcmp(savedTokens[i],andd)==0)   return ret;
        if(strcmp(savedTokens[i],orr)==0)   return ret;
        if(strcmp(savedTokens[i],semi)==0)   return ret;
        if(strcmp(savedTokens[i],piper)==0)   return ret;
       // if(strcmp(savedTokens[i],num)==0)   return ret;
       // if(strcmp(savedTokens[i],anum)==0)   return ret;

    }
    return ret;
}
//EXEC HELPER FUNCTION
bool execute(char* args[],string ctype,char** savedTokens ){
   // int savein;
   // vector<string> connectors;
   // if(-1==(savein=dup(STDIN_FILENO))){
   // perror("error in stdin dup");    
   // }
   
    int pipefd=-1;
    if(isin(savedTokens,">")){ // output append
        size_t i=0;
        for(;strcmp(savedTokens[i],directout.c_str())!=0;i++){
        }
        i++;
        //cout<< "execute i: " << savedtoken 
        pipefd = open(savedTokens[i], O_WRONLY|O_CREAT|O_TRUNC,0777);
        if(-1==pipefd){
            perror("error on open in execute in redirout");
            exit(1);
        }

    }
    else if(isin(savedTokens,">>" ) ){
        size_t i=0;
        for(;strcmp(savedTokens[i],directout.c_str())!=0;i++){
        }
        i++;
        //cout<< "execute i: " << savedtoken 
        pipefd = open(savedTokens[i], O_WRONLY|O_CREAT|O_APPEND,0777);
        if(-1==pipefd){
            perror("error on open in execute in aredirout");
            exit(1);
        }

    }

    if(isin(savedTokens,"<")){ // is input redir
        
        size_t i=0;
        for(;strcmp(savedTokens[i],piper.c_str())!=0;i++){
        }
        i++;
        //cout<< "execute i: " << savedtoken 
        pipefd = open(savedTokens[i], O_RDONLY);
        if(-1==pipefd){
            perror("error on open in execute");
            exit(1);
        }
    }
    int success = -1; 
    success= execvp(savedTokens[0],savedTokens);
    if(success == -1){
        perror("error on execvp in execute");
        exit(0);
    }
    if(success==0){
    return true;
    }
    else if(success>0){
    return false;    
    }

}

/*
    int pid=fork();
    int status=0;
    if(pid==-1){
		perror("error in fork");
        exit(1);
	}
	/////////////////////////////////
    //IF IN CHILD PROCESS
    /////////////////////////////////
   else if (pid ==0) {
        
           // piping
                            status=execvp(args[0],args); // normal code
            
            if(status!=0){
                perror("error in execvp");
            }
           
            exit(1);
        }

  	
    //////////////////////////////
    //IF IN PARENT PROCESS
    //////////////////////////////
	else if (pid>0) {
        int result=waitpid(pid,&status,0);
            if(result==-1){
            perror("error in wait");
        }
        if( status==0){ // SUCCESSS
            if(ctype=="eol")       // EOL
                return false;
             if(ctype=="or")      // OR
                return false;
             if(ctype=="semi")      // SEMI
                return true;
              if(ctype=="and")   // AND
                return true;
       }
       else if(status>0) { //FAILURE
              if(ctype=="eol")   //EOL
                return false;
              if(ctype=="or")   //OR
                return true;
              if(ctype=="semi")   //SEMI
                return true;
              if(ctype=="and")    //AND
                return false;
            }
       }
    return true;
}
*/

void Tokenizer(char* cmd,vector<char> &myvector, char** savedTokens) {
    char connectorparsed[32000];
    /*
     for(size_t q=0;cmd[q]!='\0';q++){
            cout << cmd[q];
        }
    cout << endl;
    */
    //strcpy(connectorparsed,cmd);
    for(int i=0;cmd[i]!='\0';i++){
        //cout<< " #: " << i << endl;
        if( cmd[i]==';' ){
            myvector.push_back(' ');
            myvector.push_back(cmd[i]);
            myvector.push_back(' ');
        }
        else if( cmd[i]=='<' ){
            myvector.push_back(' ');
            myvector.push_back(cmd[i]);
            myvector.push_back(' ');
        }
        else if( cmd[i]=='&' && cmd[i+1]=='&'){
                myvector.push_back(' ');
                myvector.push_back(cmd[i]);
                myvector.push_back(cmd[i]);
                myvector.push_back(' ');
                i++;
                //cout<< " double: " << i << endl;
            
        }

        else if(cmd[i]=='|'){       // | and ||
            if(cmd[i+1]!='|'){
                myvector.push_back(' ');
                myvector.push_back(cmd[i]);
                myvector.push_back(' ');
             }
            else{
            myvector.push_back(' ');
            myvector.push_back(cmd[i]);
            myvector.push_back(cmd[i]);
            myvector.push_back(' ');
            i++;
             }
        }

        else if(cmd[i]=='>'){       // > and >>
                if(cmd[i+1]!='>'){
                    myvector.push_back(' ');
                    myvector.push_back(cmd[i]);
                    myvector.push_back(' ');

                
                }
                else{
                    myvector.push_back(' ');
                    myvector.push_back(cmd[i]);
                    myvector.push_back(cmd[i]);
                    myvector.push_back(' ');
                    i++;
                   }
        }
        else{
            myvector.push_back(cmd[i]);
        }
    }

    for(size_t i=0;i<myvector.size();i++){
        connectorparsed[i]=myvector.at(i);
    }
    char* tokens= strtok(connectorparsed," ");
    
    
    int tokenindex=0;
   
    //cout << "token indexes " << tokenindex <<endl;
    while(tokens!= NULL){
    
        savedTokens[tokenindex]= strdup(tokens);
        
        for(size_t q=0;savedTokens[tokenindex][q]!='\0';q++){
           // cout << savedTokens[tokenindex][q];
        }
        //cout << endl;
        
        tokenindex++;
        //cout<< tokenindex << endl;
		tokens=strtok(NULL," ");
	}                   // done tokenizing
    
    //savedTokens[tokenindex]=NULL;
    tokenindex=0; 
   // isin(savedTokens,"<");
}


void piping(char** args,string ctype,bool &run,char** savedTokens) { 
    int pipefd[2];
    char* lhs[3200];
    char* rhs[3200];
    size_t i=0;
    size_t j=0;
    int len=0;
    bool status=false;
    if(isin(savedTokens,"|")==false) {
        status=execute(args,ctype,savedTokens);
     
        if(status){ // SUCCESSS
            if(ctype=="eol")       // EOL
                run= false;
            else if(ctype=="or")      // OR
                run= false;
            else if(ctype=="semi")      // SEMI
                run= true;
            else if(ctype=="and")   // AND
                run= true;
       }
       else if(status) { //FAILURE
              if(ctype=="eol")   //EOL
                run= false;
              else if(ctype=="or")   //OR
                run= true;
              else if(ctype=="semi")   //SEMI
                run true;
              else if(ctype=="and")    //AND
                run false;
        }

    }
    else{
        for(; strcmp(savedTokens[i],piper.c_str())!=0;i++){
          cout<<i<< ": " << lhs[i] <<endl;
          lhs[i] = savedTokens[i];
            
        }
        cout << i << ": last" << endl;
        lhs[i]=NULL;
        i++;
        for(;savedTokens[i]!='\0';i++,j++){
            cout<<j<<"::last"<<rhs[j]<<endl;
            rhs[j] = savedTokens[i];
            
        }
        rhs[j]=NULL;
        
        if(pipe(pipefd)== -1){
            perror(" error on pip");
            exit(1);
        }
        int pid = fork();
        if(-1== pid){
            perror("error on fork");
            exit(1);
        }
        /////////////////////////////////
        //IF IN CHILD PROCESS
        /////////////////////////////////
        
        else if (pid ==0) {
            int err = dup2(pipefd[1],1);
            if(-1==err){
                perror("error on dup2 in child");
                exit(1);
            }
            err= close(pipefd[0]);
            if(=1==err){
                perror("error on close in child");
                exit(1);
            }
            run=execute(args,ctype,savedTokens);
        }

        //////////////////////////////
        //IF IN PARENT PROCESS
        //////////////////////////////
        else if(pid>0){
            if(close(pipefd[1]) == -1){
                perror("error on close in parent");
                exit(1);
            }
            int savestdin= dup(0);
            if(-1 == savestdin){
                perror("error on dup in parent");
                exit(1);
            }
            if(-1 == dup2(pipefd[0],0)){
                perror("error on dup2 in parent");
                exit(1);
            }
            if(wait(0) == -1){
                perror("error on wait in parent");
                exit(1);
            }
            piping(args,ctype,run,savedTokens);
            if(-1== dup2(savestdin,0)){
                perror("error on restoring dup2 in parent");
                exit(1);
            }


        }

    }
}

 
int main(){

    string user;
    char host[3200];
    user= getlogin();
    gethostname(host,3200);
	string str="";
	char cmd[320000];


	char* savedTokens[32000];

    vector<char> myvector;
    
       bool run=true;
    string connector="";
    // I/O redirection
    

    while(1){
        run=true;
        myvector.clear();
        cout<<user<<"@"<<host<< "$ ";
        getline(cin,str);		// get input at str
        int loc=0;              // erase comments
        if((loc = str.find("#"))!=0){
            str = str.substr(0,loc);
        }
        else
            continue;
        strcpy(cmd,str.c_str());	// get c string of str
        //cout << "hey" << endl;
        Tokenizer(cmd,myvector,savedTokens);
        //cout << "red" << endl;
        /*
        for(size_t q=0;savedTokens[tokenindex][q]!='\0';q++){
            cout << savedTokens[tokenindex][q];
        }
        cout << endl;
        */



        if(strcmp(exitS,savedTokens[0])==0||strcmp(exitB,savedTokens[0])==0){
            return 0; // called exit
        }
        //cout << " not yet" << endl;
        char* args[3333];
        string ctype="eol";
        for(int i=0, j=0;run;i++,j++){
           // cout<< savedTokens[i]<<endl;
            if(savedTokens[i]==NULL){
                args[j]=NULL;
                piping(args,ctype,run,savedTokens); 
             //run=execute(args,ctype);
              break;
            }
            else if(strcmp(savedTokens[i],andd)==0){
               // cout<<" ANDD"<< endl;
                ctype="and";
             }
            else if(strcmp(savedTokens[i],orr)==0){
              // cout<< "ORR" << endl;
                ctype="or";
             }
            else if(savedTokens[i][0] == semi[0] && savedTokens[i][1] == '\0'){
              // cout << "SEMI"<< endl;
                ctype="semi";
               // cout << "semi"<< endl;
             }
            else if(strcmp(savedTokens[i],directin)==0){
              // cout<< "directin" << endl;
                ctype="dirin";
             }
            else if(strcmp(savedTokens[i],directout)==0){
              // cout<< "directout" << endl;
                ctype="dirout";
             }
            else if(strcmp(savedTokens[i],apdirectout)==0){
              // cout<< "apdirectout" << endl;
                ctype="adirout";
             }
            else if(strcmp(savedTokens[i],piper)==0){
              // cout<< "piper" << endl;
                ctype="pipe";
             }
            else{                                          // when it is a command
                args[j]=savedTokens[i];
              // cout << "arg: "<<savedTokens[i]<<endl;
              // cout<< "andd: " << andd << endl;
                continue;
            }
            piping(args,ctype,run,savedTokens); 
            //run=execute(args,ctype);
            j=-1;
        }

        
   }
}


