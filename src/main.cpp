#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
using namespace std;

int main(int arc, char **argv){
	char str[32000];
	char *cmd;
	while(1){
	//cout path
	cout<< endl<< "$ ";
	cin.getline(str,32000);
	cmd = strtok(str," ");
		while(cmd!= NULL){
			cout<<cmd;
			cmd=strtok(NULL," ");
		}
	
	}	


	int pid=fork();
	if(pid=-1){
		perror("fork fail");
	}
	else if (pid ==0) {
		if(execvp(cmd,argv)!=0){
		perror("error in execvp");
		}
	}
	else {
		cerr << "will this print?!" <<endl;
	}
	return 0;
}
	
                                                                                                                       
                                   
