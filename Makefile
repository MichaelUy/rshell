FILEPATH= ./src/main.cpp
FILEPATH1=./src/scriptls.cpp
OUTPATH= ./bin/rshell
OUTPATH1= ./bin/ls
CPPFLAGS = -Wall -Werror -ansi -pedantic
POWER= g++
objects = $(addprefix obj/, main.o)
all:
	mkdir -p ./bin
	$(POWER) $(FILEPATH) $(CPPFLAGS) -o $(OUTPATH)
	$(POWER) $(FILEPATH1) $(CPPFLAGS) -o $(OUTPATH1)

rshell:
	mkdir -p ./bin
	$(POWER) $(CPPFLAGS) $(FILEPATH) -o $(OUTPATH)

ls:
	mkdir -p ./bin
	$(POWER) $(CPPFLAGS) $(FILEPATH1) -o $(OUTPATH1)

clean:
	rm -rf ./bin

