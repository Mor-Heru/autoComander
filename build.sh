apt install libncurses-dev


g++ -c source/comand.h
g++ -c source/comand.cpp

g++ -c source/line.h
g++ -c source/line.cpp

g++ -c source/terminal.h
g++ -c source/terminal.cpp

g++ -c source/main.cpp

g++ main.o terminal.o comand.o line.o -o main -lncurses