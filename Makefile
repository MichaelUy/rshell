FILEPATH= ./src/main.cpp

CPPFLAGS = -Wall -Werror -ansi -pedantic
objects = $(addprefix obj/, main.o)
all:$(OBJS)
	mkdir bin
	g++ $(FILEPATH) -o bin/rshell $(CPPFLAGS)
bin/rshell: $(objects) | bin
	cc -o $@ $(objects)

obj/%.o: %.c
	cc $(CFLAGS) -c -o $@ $<

$(objects): | obj



obj:
	mkdir obj

clean:
	rm -rf obj bin

