#Summary
rshell is a simple shell that is able to run basic syscalls utilizing:
#HW3 Summary
For HW3 I implemented my own version of cd, custom SIGNAL ^C,and used the execv syscall instead of the execvp syscall which required getenv() to get the PATH variable.
-supports:
- cd to a directory with a relative path
- cd to a directory with an absolute path
- cd to previous (..) directory
- Special Case: cd without a directoy notifies the user there there is noe directory specified
- ^c signal  is ignored in rshell when nothing is running
- ^c signal kills the child when an executable is running, such as cat
-  my rshell supports commands that are located in diffrent directories by using getenv() and attempting to find the commands in multiple directories
-  if the command does not exist, my rshell throws an error notifying the user that the command does not exists

#known bugs and limitations
- did not implement ^z
- STILL DOES NOT HAVE PIPING, PIPING HURTS,OH GOD
- connectors usually don't work
- io redirection does not work for ls and cd


#HW2 Summary
For HW2 I implemented my own I/O Redirection symbols  which requires  the manipulation of file descriptors
- supports:
- executable<file #(existentfile or not) 
- executable>file #(existentfile or not)
- executalbe>>file #(existentfile or not; if existent it will append) 
- wc<text>text2 #this passes text into word count and reaps the output into text2
- wc<text>>text2 #this passes text into word count and reaps the output and appends it to text2
- CONNECTORS ARE NOT FUNCTIONING I TRIED I DID BUT MY BEST WAS NOT IN THE LEAST SUFFICENT
- PIPING DOES NOT WORK, I DEVOTED HALF MY CODE TO THEM, BUT ALAS THE SLINGS AND ARROWS OF FATE

# HW1 Summary
For HW1 I implemented my own ls command. It is as close to GNU ls as possible (plus magenta "hidden" colorizing):
- supports: -a,-l,-R, and any combination of the three (i.e. -al, -lR, -Rla, and ect.)
- can take in 0,1,+1 path arguments
- uses  perror on: opendir,closeddir,readdir stat
# HW1 EXTRA CREDIT & FEATURES
EXTRA CREDIT: uses ANSI escape codes to display diffrent types of files in color
-Supports:
- directories: blue text, BOLD
- links: cyan text, BOLD
- pipe: yellow text, black background
- socket: magenta text, BOLD
- block devices: yellow text, black background, BOLD
- character device: yellow text, black background, BOLD
- executables: green text
- HIDDEN FILES: I chose to give a magenta background (instead of grey) to hidden files for readability
I chose to follow the Gnu ls color coding standards
![alt tag](http://i.stack.imgur.com/gnT32.png)

- On invalid flag call, I report the flag that threw the error
- return "ls: cannot run invalid flag '<invalid flag here>'"
# HW1 TEST CASES
-  ./ -R
- ../ -R
- -a
- -l
- -R
- -z
- -R -R
- -R-R
- -laR
- ///////
- -
- ---
- src
- src -a
- src -l
- src -R
- src -Rla
- src -l
- src/ -R
- src src
- src src -l
- src src -a
- -a src src
- -l src src
- -R src src
- -la src src
- -lR src SRC
- . src src ..
- ...
- -lll
- fakefile
- . . . . . . . . . . . . . . . . . . .
- ~
- \

# HW1 KNOWN BUGS
- if memory takes more that 6 digit spaces, -l output becomes mis aligned
- non -a  outputs are not alligned into columns
- .//
- \
- ////////

# HW0 Summary
For HW0 I created rshell. rshell is a simple shell that is able to run basic syscalls utilizing

- ls and its flags, cheifly -a,-A,-l,-R,-s,-S and the sort
- echo followed by text or no text
-combinational operators ';','&&','||'
- ignores white space, though flags that are touching commands are errors as per usual
- supports both "exit" and "Exit" commands


#Test Cases
# ls tests
1) ls
2) ls -a
3) ls -aRl
4) ls -a-R-l
5) ls -a -OneFlagThatExistsAndAnotherThatDoesnt
6) & ls
7) ls &
8) ls &&
9) && ls
10) ls ls ls ls ls
# combinational operators tests
1) ls||echo
2) ls || echo
3) ls && echo
4) ls||&&echo
5) ls|&|&|&|&echo
6) ls;echo;echo
7) ls;;echo
8) ||
9) ;
10) ;&&||
# comments and command variations tests
1) #hi
2) echo # hi
3) #
4) ## hi
5) ls # -a
6) ls -l ; # test
7) cd #
8) #echo && echo || echo test
9) ls|| # test
10) echo tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt#tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
# true and false example tests
1) true || echo
2) false || ls
3) true; false||ls
4) false && echo
5) true && echo
6) false; ls
7)  ls -a false
8) ls true && echo
9) true && false || echo wow
10) false || true && wow
# miscellaneous destruction attemps
1) ls -aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
2) false || false || false || false || false || false || false || false || ls -l
3)  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;&& ls
4)  false |||||| echo
5) cat nonexistantfile.cpp
6) cat echo
7) echo cat
8) ls cat ls echo ls cat
9) ls -X-x-U-V
10) echo 123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789vvvvv123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789


#Known Bug
- Buffer only holds up to 32000 characters
- getting a "is not a file and directory" error on ls brings that error to other ls's
- "#" commenting doesn't work when put in a field of other characters (ex. "ttttttttttttttttttt#tttttttttttttttttt")
- ls -a-R-l throws an syntatcicall error on '-'
- cat has a simillar issue as ls when it comes to not finding and file or directory
- ls sees combinational operators as arguments on occasion
- more bugs exist that have missed my eye

