#ifndef CAPICONN_H
#define CAPICONN_H

#include"capiex.hxx"
#include"capimsg.hxx"
#include"capiobj.hxx"

class CAPIConnection {

protected:

	_cdword NCCI;
	bool onHold,txData;

	CAPIobj *capi;

public:
	CAPIConnection();
	CAPIConnection(CAPImsg *msg,CAPIobj *Capi);
	~CAPIConnection();

	_cdword getNCCI();

	void connectind(CAPImsg *c);
	void connectactiveind(CAPImsg *c);
	void disconnectind(CAPImsg *c);
};

#endif
