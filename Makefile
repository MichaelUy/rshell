FILEPATH=./src/main.cpp
FILEPATH1=./src/ls.cpp
FILEPATH2= ./src/cp.cpp
OUTPATH= ./bin/rshell
OUTPATH1= ./bin/ls
OUTPATH2= ./bin/cp
CPPFLAGS = -Wall -Werror -ansi -pedantic
POWER= g++
objects = $(addprefix obj/, main.o)
all:
	mkdir -p ./bin
	$(POWER) $(FILEPATH)  $(CPPFLAGS) -o $(OUTPATH)
	$(POWER) $(FILEPATH1) $(CPPFLAGS) -o $(OUTPATH1)
	$(POWER) $(FILEPATH2) $(CPPFLAGS) -o $(OUTPATH2)

rshell:
	mkdir -p ./bin
	$(POWER) $(CPPFLAGS) $(FILEPATH) -o $(OUTPATH)

cp:
	mkdir -p ./bin
	$(POWER) $(CPPFLAGS) $(FILEPATH2) -o $(OUTPATH2)

ls:
	mkdir -p ./bin
	$(POWER) $(CPPFLAGS) $(FILEPATH1) -o $(OUTPATH1)

clean:
	rm -rf ./bin

