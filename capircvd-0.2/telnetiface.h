#include<iostream>
#include<fstream>
#include<strstream>
#include<string>
#include"tools.h"

// socket and telnet-stuff...

int response(fstream &f,string aus,string &ein);
void * telnetserver_func(void *a);
void * acceptthread_func(void * x);

