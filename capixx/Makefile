
main : capixx.o capiobj.o capiex.o capimsg.o main.o ; gcc main.o capiobj.o capixx.o capiex.o capimsg.o -o main -lstdc++ -ldl

main.o : main.cxx ; gcc -c main.cxx -o main.o

capixx.o : capixx.cxx ; gcc -c capixx.cxx -o capixx.o

capiobj.o : capiobj.cxx ; gcc -c capiobj.cxx -o capiobj.o

capiex.o : capiex.cxx ; gcc -c capiex.cxx -o capiex.o 

capimsg.o : capimsg.cxx ; gcc -c capimsg.cxx -o capimsg.o

test : main ; ./main

clean : ; rm *.o

