
#include"capiex.hxx"

typedef void _cmsg;
typedef unsigned long tNCCI;

class CAPIxxConnection {

protected:

	tNCCI NCCI;
	bool onHold,txData;

public:
	CAPIxxConnection() {};
	~CAPIxxConnection() {};

	void setNCCI(tNCCI ncci) {
		NCCI=ncci;
	}

	tNCCI getNCCI() {
		return NCCI;
	}

	void connectind(_cmsg *CMSG) {
	};
	void disconnectind() {
	};
};

