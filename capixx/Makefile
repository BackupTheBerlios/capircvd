
main : capixx.o capiobj.o capiex.o capimsg.o main.o ; gcc -g main.o capiobj.o capixx.o capiex.o capimsg.o -o main -lstdc++ -ldl

main.o : main.cxx ; gcc -g -c main.cxx -o main.o

capixx.o : capixx.cxx ; gcc -g -c capixx.cxx -o capixx.o

capiobj.o : capiobj.cxx ; gcc -g -c capiobj.cxx -o capiobj.o

capiex.o : capiex.cxx ; gcc -g -c capiex.cxx -o capiex.o 

capimsg.o : capimsg.cxx ; gcc -g -c capimsg.cxx -o capimsg.o

test : main ; ./main

clean : ; rm *.o main *.ncb *.opt *.plg

