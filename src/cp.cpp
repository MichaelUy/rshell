#include <stdio.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "Timer.h"
#include <iostream>

#define TimeLord(x, y) x.elapsedWallclockTime(y); \
		cout <<"get/put wallclock " <<  # x << ": " << y  << endl; \
		x.elapsedUserTime(y); \
		cout <<"get/put user " << # x << ": " << y  << endl; \
		x.elapsedSystemTime(y); \
		cout <<"get/put system " << # x << ": " << y << endl;

using namespace std;

void checkprint(char* arg_v); 
void getcp(char* in, char* out);

int main(int argc, char** argv) {
	bool opt = false;
	char buf;
	char bf[BUFSIZ];

	if(argc < 3 || argc > 4) {
		cout << "Error! Incorrect number of arguments.\n";
		exit(1);
	}
	if(argc == 4) {
		opt = true;
	}

	char* inp = argv[1];
	char* out = argv[2];

/*	ifstream cpy;
	cpy.open(inp, ifstream::in);
	if(!cpy.is_open()) {
		cout << "Error! Problem opening input file.\n";
		exit(1);
	}
*/
	struct stat target;
	if(stat(out, &target) == 0) {
		cout << "Error! Output file already exits.\n";
		exit(1);
	}

/*	ofstream pste;
	pste.open(out);
	if(!pste.is_open()) {
		cout << "Error! Problem opening output file.\n";
		exit(1);
	}
*/
	if(opt) {	
		Timer t0;	// get char
		double et0;
		Timer t1;	// read char
		double et1;

		t0.start();		// t0 timer started
		getcp(argv[1], argv[2]);	// call get function
		TimeLord(t0, et0);	// cout t0 time
/*		cpy.close();
		pste.close();
*/
//		checkprint(argv[2]);

		cout << "---------------------------" << endl;

		ifstream cpy;
		ofstream pste;
		cpy.open(inp, ifstream::in);
		pste.open(out);
		t1.start();

		int hold;
		int hold2;	
		if(stat(out, &target) == -1){
			hold = open(argv[2], O_WRONLY | O_TRUNC);	
		}
		else{
			hold = open(argv[2], O_WRONLY | O_CREAT);
		}
		if(stat(inp, &target) == -1){
			hold2 = open(argv[1], O_RDONLY | O_TRUNC);
		}
		else{
			hold2 = open(argv[1], O_RDONLY | O_CREAT);
		}

		while(read(hold2,&buf,1)) {
			write(hold, &buf, 1);
		}
		
		TimeLord(t1, et1);
		cpy.close();
		pste.close();

//		checkprint(argv[2]);

		cout << "---------------------------" << endl;
	}

	ifstream cpy;
	cpy.open(inp, ifstream::in);
	if(!cpy.is_open()) {
		cout << "Error! Problem opening input file.\n";
		exit(1);
	}

	ofstream pste;
	pste.open(out);
	if(!pste.is_open()) {
		cout << "Error! Problem opening output file.\n";
		exit(1);
	}

	Timer t2;	// read buf
	double et2;	
	t2.start();
	int hold3;
	int hold4;

	if(stat(out, &target) == -1){
		hold3 = open(argv[2], O_WRONLY | O_TRUNC);	
	}
	else{
		hold3 = open(argv[2], O_WRONLY | O_CREAT);
	}
	if(stat(inp, &target) == -1){
		hold4 = open(argv[1], O_RDONLY | O_TRUNC);
	}
	else{
		hold4 = open(argv[1], O_RDONLY | O_CREAT);
	}

	int rock = read(hold4, &bf, BUFSIZ);
	while(rock) {
		if(rock == -1) {
			perror("read");
			exit(1);
		}
		if(write(hold3, &bf,rock ) == -1) {
			perror("write");
			exit(1);
		}
		rock = read(hold4, &bf, BUFSIZ);
	}

	if(opt) { TimeLord(t2, et2); }

	cpy.close();
	pste.close();

//	checkprint(argv[2]);

	cout << endl;	
	return 0;
}

void checkprint(char* arg_v) {
	cout << endl << endl;
	ifstream read;
	read.open(arg_v);
	char c;
	while(read.get(c)) { cout << c; }
	read.close();
}

void getcp(char* in, char* out) {
	ifstream cpy;
	cpy.open(in, ifstream::in);
	if(!cpy.is_open()) {
		cout << "Error! Problem opening input file.\n";
		exit(1);
	}

	ofstream pste;
	pste.open(out);
	if(!pste.is_open()) {
		cout << "Error! Problem opening output file.\n";
		exit(1);
	}
	char c;
	while(cpy.get(c)) {
		pste.put(c);
	}
}


