#include"capiex.hxx"

Ex::Ex(unsigned char *c) {
 Error=c;
}

Ex::Ex(char *c) {
 Error=(unsigned char*)c;
}

unsigned char *Ex::Msg() {
 return Error;
}
