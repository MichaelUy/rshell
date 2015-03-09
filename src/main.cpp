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
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

bool green = true;
char exitS[]="exit";
char exitB[]="Exit";
char directin[]={'<','\0'};
char directout[]={'>','\0'};
char apdirectout[]={'>','>','\0'};
char piper[]={'|','\0'};

char andd[]={'&','&','\0'};
char orr[]={'|','|','\0'};
char semi[]={';','\0'};

void nothing(int sig){


        
    int pid= getpid();
    if(pid==-1){
        perror("error on getpid");
        exit(1);
    }
    if(pid==0){
       // raise(SIGINT);
        exit(0);     
    }


}

void rshell();
/*
bool commandexits(const char *command){
    struct stat the_goods;
    if( -1== stat(command, the_goods)){
        


    }


}
*/
bool isin(char** savedTokens,string search ){
    bool ret = false;
    for(size_t i=0;savedTokens[i]!=NULL;i++){
      if(strcmp(savedTokens[i],search.c_str())==0){
         // cout << savedTokens[i][0] << " x " << search<< endl;
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
void execute(char* args[],string ctype,char** savedTokens, bool &run  ){
   // int savein;
   // vector<string> connectors;
   // if(-1==(savein=dup(STDIN_FILENO))){
   // perror("error in stdin dup");    
   // }
   //
   //cout << " execution" << endl;
   // signal(SIGINT, SIG_DFL);
    bool inp=false;
    bool outp=false;
    char cd[3]={'c','d','\0'};
    int fd;
    int fd2;
    //int file;
    int savestdin;
    int savestdout;
   // signal(SIGTSTP, handler);

   /*
    printf(args[0],4);
    cout << endl;
    printf(args[1],4);
    cout << endl;
    */
    if(strcmp(args[0],cd)==0){
       // cout<< "caught" << endl;
        if(args[1] == '\0'){
            run=false;
            cout<< "no directory specified" <<endl;
             
        }
        else if(chdir(args[1])==-1){
            run=false;
            perror("error on chdir");
            
        }
        else
            run=true;
     //   cout<< "changed dir" << endl;

        exit(1);
    }
    if(isin(savedTokens,"<")== true){ // is input redir
        inp=true;
         savestdin = dup(0);
            if(-1==savestdin){
                perror("error on dup");
                exit(1);
            }


        size_t i=0;
        for(;strcmp(savedTokens[i],directin)!=0;i++){
        }
        //cout<< savedTokens[i][0]<<endl;
        i++;
    //access
        if(-1==access(savedTokens[i],F_OK)){
            perror("error on access");
            exit(1);
        }
    // open
        fd = open(savedTokens[i], O_RDONLY);
        if(-1==fd){
            perror("error on open in execute");
            exit(0);
        }
    // dup2
        if(-1== dup2(fd,0)){
        perror("error on dup2 exec");
        exit(1);
    }
    //????

        }

////////////////////////////////////////////////////////////output replace
    if(isin(savedTokens,">")== true){ // output reg
        outp=true;
     //save out
        savestdout = dup(1);
            if(-1==savestdout){
                perror("error on dup");
                exit(1);
            }
        size_t i=0;
        for(;strcmp(savedTokens[i],directout)!=0;i++){
        }
        i++;
    //access
        if(access(savedTokens[i],F_OK)!=-1){
    //open and exists
            fd2 = open(savedTokens[i], O_WRONLY|O_TRUNC,00777);
        if(-1==fd2){
            perror("error on open in execute in redirout");
            exit(0);
        }
        }  // open and created
          else{
        fd2 = open(savedTokens[i], O_WRONLY|O_CREAT,00777);
        
        if(-1==fd2){
            perror("error on open in execute in redirout");
            exit(0);
        }
        }
    // dup2
        if(-1== dup2(fd2,1)){
        perror("error on dup2 exec");
        exit(1);
        }
        
    }////////////////////////////////////////////////////////////output append
    else if(isin(savedTokens,">>" )== true ){
        outp=true;
     //save out
         savestdout = dup(1);
            if(-1==savestdout){
                perror("error on dup");
                exit(1);
            }


        size_t i=0;
        for(;strcmp(savedTokens[i],apdirectout)!=0;i++){
        }
        i++;
    // access
        if(access(savedTokens[i],F_OK)!=-1){

    //open    append
        fd2 = open(savedTokens[i], O_WRONLY|O_APPEND,00744);
        if(-1==fd2){
            perror("error on open in execute in aredirout");
            exit(0);
        }
        }
    // open create
        else{
        fd2 = open(savedTokens[i], O_WRONLY|O_CREAT,00744);
        if(-1==fd2){
            perror("error on open in execute in aredirout");
            exit(0);
        }
        }
   // dup2
        if(-1== dup2(fd2,1)){
        perror("error on dup2 exec");
        exit(1);
        }
        

    }
/*
 for(int r=0;savedTokens[r]!='\0';r++){      // super memory leak fix attempt
        free(savedTokens[r]);
        }
*/
///////////////////////////////////////////////////////////////////////////input
    //save in
    //cout << " have arrived to exec"<< endl;///////////////////////execvp
    
    vector<string> mypathvector;

    char masterpath [BUFSIZ];
        if(NULL==getcwd(masterpath,sizeof(masterpath))){
            perror("error on getcwd");
            exit(1);
        }
    string currentdirectory= string(masterpath);
    mypathvector.push_back(masterpath);
    
    // gather paths
    
    const char*env = getenv("PATH");
    if(env==NULL){
        perror("error on getenv");
        exit(1);
    }

    char *hold = new char[strlen(env + 1)];
    strcpy(hold, env);
    char * tokeniz = strtok(hold,":");
    
    // while loop
    while (tokeniz != NULL){

        mypathvector.push_back(tokeniz);
        tokeniz=strtok(NULL,":");
    }
    delete[] hold;
 bool checking=false;
 for(size_t  i=0; i< mypathvector.size();i++){
    string attemptpath=mypathvector[i];
    attemptpath = attemptpath + "/" + args[0];
    
    if(access(attemptpath.c_str(),F_OK)==0){
        perror("error on access");
        
    
    }
     if(access(attemptpath.c_str(),F_OK)==0){
        checking=true;
    } 
    execv(attemptpath.c_str(),args);
    
   
  }


 if(!checking){
        cerr<< "rshell: " << string(args[0]) << ": command not found"<<endl;
    }
/*
if(-1== execvp(args[0],args)){
    perror("error on execvp in execute");
    exit(1);
}
*/

/*
if(-1== close(fd)){////////////////////////////////////////// restore
 
                perror("error on close in exec");
                exit(1);
 } */
if( inp){
    inp=false;

    ///////////////////////////////////////////////////close input to file
if(-1== close(fd)){
 
                perror("error on close in exec");
                exit(1);
 }
 //////////////////////////////////////////////////////////// restore save stdin
 if(-1== dup2(savestdin,0)){
        perror("error on dup2 exec");
        exit(1);
    }


   }
if(outp ){
    outp = false;
   //////////////////////////////////////////////////////  close output to file 
    if(-1== close(fd2)){
 
                perror("error on close in exec");
                exit(1);
///////////////////////////////////////////////////////// restore save stdout
     if(-1== dup2(savestdout,1)){
        perror("error on dup2 exec");
        exit(1);
    }
 }
   }


//cout << "exec over" << endl;
exit(0);
}


void piping(char** args,string &ctype,bool &run,char** savedTokens) { 
    int pipefd[2];
    //char* lhs[3200];
    char* rhs[3200];
   // signal(SIGINT,nothing);
    //size_t j=0;
    //int len=0;
    //bool status=false;
    int status;
    if(isin(savedTokens,"|")==false) {
       

        execute(args,ctype,savedTokens,run);
    }
        else{
        int i=0;
        int j=0;
        
        for(; strcmp(savedTokens[i],piper)!=0;i++){
         // cout<<i<< ":: " << savedTokens[i] <<endl;
         // lhs[i] = savedTokens[i];
            
        }
       // cout << i << ": last == null" << endl;
        //lhs[i]=NULL;
        i++;
        for(;savedTokens[i]!='\0';i++,j++){
         //   cout<<j<<"::last"<<rhs[j]<<endl;
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

        if(dup2(pipefd[1],1) == -1){
        perror("error on dup2");
        exit(1);
        }

        if(close(pipefd[0]) == -1){
            perror("error on close");
            exit(1);
        }
            vector<string> mypathvector;

    char masterpath [BUFSIZ];
        if(NULL==getcwd(masterpath,sizeof(masterpath))){
            perror("error on getcwd");
            exit(1);
        }
    string currentdirectory= string(masterpath);
    mypathvector.push_back(masterpath);
    
    // gather paths
    
    const char*env = getenv("PATH");
    if(env==NULL){
        perror("error on getenv");
        exit(1);
    }

    char *hold = new char[strlen(env + 1)];
    strcpy(hold, env);
    char * tokeniz = strtok(hold,":");
    
    // while loop
    while (tokeniz != NULL){

        mypathvector.push_back(tokeniz);
        tokeniz=strtok(NULL,":");
    }
    delete[] hold;

 for(size_t  i=0; i< mypathvector.size();i++){
    string attemptpath=mypathvector[i];
    attemptpath +="/";
    attemptpath += args[0];
    execv(attemptpath.c_str(),args);
  }
       
             
        }

        //////////////////////////////
        //IF IN PARENT PROCESS
        /////////////////////////////
        
        else if(pid>0){
            
           // cerr << " PARENT " << endl;
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
            //cout << " in parent, wait"<<endl;
            if(waitpid(pid,&status,0) == -1){
                perror("error on wait in parent");
                exit(1);
            }
           //  cout <<" superstatus: " << status<< endl;   
        if(status==0){ // SUCCESSS
            if(ctype=="eol")       // EOL
                run= false;
            else if(ctype=="or")      // OR
                run= false;
            else if(ctype=="semi")      // SEMI
                run= true;
            else if(ctype=="and")   // AND
                run= true;
           else if (ctype=="directout")
               run=false;
           else if(ctype=="directin")
               run=false;
            else
                run= true;
       }
       else if(status>0) { //FAILURE
              if(ctype=="eol")   //EOL
                run= false;
              else if(ctype=="or")   //OR
                run= true;
              else if(ctype=="semi")   //SEMI
                run= true;
              else if(ctype=="and")    //AND
                run= false;
              else if (ctype=="directout")
               run=false;
              else if(ctype=="apdirectout")
               run=false;
              else
                  run = false;
        }
            if( rhs[0] != NULL){
            piping(rhs,ctype,run,savedTokens);
            }
            if(-1== dup2(savestdin,0)){
                perror("error on restoring dup2 in parent");
                exit(1);
            }


        }

    }
   // cout << " in piping checking run: " << run<< endl;
   /*
    for(int r=0;savedTokens[r]!='\0';r++){
        free(savedTokens[r]);
        }
    */
   rshell();
}
 
void rshell(){

    string user;
    char host[3200];
    user= getlogin();
    gethostname(host,3200);
	string str="";
	char cmd[320000];
    signal(SIGINT, nothing);
    //signal(SIGINT, SIG_IGN);
	char* savedTokens[32000];

    vector<char> myvector;
    
       bool run=true;
    string connector="";
    // I/O redirection
    
    while(1){
        run=true;
        myvector.clear();
        char masterpath [BUFSIZ];
        if(NULL==getcwd(masterpath,sizeof(masterpath))){
            perror("error on getcwd");
            exit(1);
        }
        cout<<user<<"@"<<host<<":~"<< masterpath <<"$ ";
        getline(cin,str);		// get input at str
        int loc=0;              // erase comments
        if((loc = str.find("#"))!=0){
            str = str.substr(0,loc);
        }
        else
            continue;
        strcpy(cmd,str.c_str());	// get c string of str
        //cout << "hey" << endl;
        //Tokenizer(cmd,myvector,savedTokens);i
        //
        //
        //
           char connectorparsed[3200];
    /*
     for(size_t q=0;cmd[q]!='\0';q++){
            cout << cmd[q];
        }
    cout << endl;
    */
    //strcpy(connectorparsed,cmd);
    if(cmd[0]=='\0'){
        continue;
    }
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
    //cout<< " ATTENTION: " << myvector.at(myvector.size()-1)<< endl;
    myvector.push_back('\0');
    for(size_t i=0;i<myvector.size();i++){
        connectorparsed[i]=myvector.at(i);
    }
    char* tokens= strtok(connectorparsed," ");
    
    
    int tokenindex=0;
   
    //cout << "token indexes " << tokenindex <<endl;
    while(tokens!= NULL){
    
       savedTokens[tokenindex]= strdup(tokens);
      
  //     free(tokens); 
      
       // cout << " tokenizer : " <<endl; 
       // for(size_t q=0;savedTokens[tokenindex][q]!='\0';q++){
       //     cout << savedTokens[tokenindex][q];
       // }
       // cout << endl;
        
        tokenindex++;
        //cout<< tokenindex << endl;
		tokens=strtok(NULL," ");
	}                   // done tokenizing
   
   
   //
   
   
    savedTokens[tokenindex]=NULL;
    tokenindex=0; 
        //
        //
        //
        //
        //cout << "red" << endl;
        /*
        for(size_t q=0;savedTokens[tokenindex][q]!='\0';q++){
            cout << savedTokens[tokenindex][q];
        }
        cout << endl;
        */



        if(strcmp(exitS,savedTokens[0])==0||strcmp(exitB,savedTokens[0])==0){
            
            green= false;
           exit(1); // called exit
        }
        //cout << " not yet" << endl;
        char* args[3333];
        string ctype="eol";
          char cd[3]={'c','d','\0'};

        for(int i=0, j=0;run;i++,j++){

                if(savedTokens[i]==NULL){
                //cout << "piping in from if" << endl;
                args[j]=NULL;
                
                int status;
                int pid = fork();

                if(-1== pid){
                perror("error on fork");
                exit(1);
                
                }
                else if (pid== 0){
                // child
                piping(args,ctype,run,savedTokens); 
                //children should exit right?
                exit(1);
                }
                else if(pid>0){
                   //  cout << " in parent, wait"<<endl;
                if(waitpid(pid,&status,0) == -1){
                    perror("error on wait in parent");
                    exit(1);
                }
                // cout <<" superstatus: " << status<< endl;   
                if(status==0){ // SUCCESSS
                    if(ctype=="eol")       // EOL
                        run= false;
                    else if(ctype=="or")      // OR
                        run= false;
                    else if(ctype=="semi")      // SEMI
                        run= true;
                    else if(ctype=="and")   // AND
                        run= true;
                    else if (ctype=="directout")
                        run=false;
                    else if(ctype=="directin")// edited to direct in
                        run=false;
                    else 
                        run = true;
               }
               else if(status>0) { //FAILURE
                      if(ctype=="eol")   //EOL
                        run= false;
                      else if(ctype=="or")   //OR
                        run= true;
                      else if(ctype=="semi")   //SEMI
                        run= true;
                      else if(ctype=="and")    //ANnD
                        run= false;
                         else if (ctype=="directout")
                        run=false;
                      else if(ctype=="apdirectout")
                        run=false;
                      else
                        run= true;
                }
                //exit(0);
                
                //rshell();
                //exit(0);
              //continue;
              
                
              break;
            }
            }
            else if(strcmp(savedTokens[i],andd)==0){
            //   cout<<" ANDD"<< endl;
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
             //  cout<< "piper" << endl;
                ctype="pipe";
             }
            else{                                          // when it is a command
                args[j]=savedTokens[i];

            if(strcmp(args[0],cd)==0 && i>0){
                //cout<< "caught" << endl;
                if(args[1] == '\0'){
                    run=false;
                    cout<< "no directory specified" <<endl;
                     
                }
                else if(chdir(args[1])==-1){
                    run=false;
                    perror("error on chdir");
                    
                }
                else{
                    run=true;
                }
                //cout<< "changed dir" << endl;
                args[j-1]='\0';
                args[j]='\0';
                j=0;
                
            }
              // cout << "arg: "<<savedTokens[i]<<endl;
//cout<< "error argcheck i: "<< i<< " j: "<<j<< " run: " << run <<endl;
              // cout<< "andd: " << andd << endl;
                continue;
            }

           // cout << "piping at end of loop run : "<< run << endl; 
            
                int status;
                int pid = fork();

                if(-1== pid){
                perror("error on fork");
                exit(1);
                
                }
                else if (pid== 0){
                // child
                piping(args,ctype,run,savedTokens); 
                //children should exit right?
                exit(1);
                }
                else if(pid>0){
                   //  cout << " in parent, wait"<<endl;
                if(waitpid(pid,&status,0) == -1){
                    perror("error on wait in parent");
                    exit(1);
                }
                // cout <<" superstatus: " << status<< endl;   
                if(status==0){ // SUCCESSS
                    if(ctype=="eol")       // EOL
                        run= false;
                    else if(ctype=="or")      // OR
                        run= false;
                    else if(ctype=="semi")      // SEMI
                        run= true;
                    else if(ctype=="and")   // AND
                        run= true;
                     else if (ctype=="directout")
                         run=false;
                     else if(ctype=="directin")
                     run=false;
                    else 
                        run = false;
               }
               else if(status>0) { //FAILURE
                      if(ctype=="eol")   //EOL
                        run= false;
                      else if(ctype=="or")   //OR
                        run= true;
                      else if(ctype=="semi")   //SEMI
                        run= true;
                      else if(ctype=="and")    //AND
                        run= false;
                       else if (ctype=="directout")
                         run=false;
                      else if(ctype=="apdirectout")
                         run=false;

                      else
                         run= false;
                }
                }
                // exit(0);
                //rshell();
                //exit(1);
                //continue;
             // break;
            


/*
            piping(args,ctype,run,savedTokens);

            rshell();
            */
            j=-1;
        
    }
    
     for(int r=0;savedTokens[r]!='\0';r++){
        free(savedTokens[r]);
        }
       
       }
}

int main(){
//signal(SIGINT,SIG_IGN);
while( green){    
rshell();
}
return 0;

}
