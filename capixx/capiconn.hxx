
#include"capiex.hxx"
#include"capimsg.hxx"

class CAPIConnection {

protected:

	_cdword NCCI;
	bool onHold,txData;

public:
	CAPIConnection();
	~CAPIConnection();

	_cdword getNCCI();

	void connectind(CAPImsg *c);
	void disconnectind(CAPImsg *c);
};

