#ifndef CAPIex_HXX
#define CAPIex_HXX

class Ex {

	unsigned char *Error;

public:
	Ex(unsigned char *c);
	Ex(char *c);
	unsigned char *Msg();
};

#endif
