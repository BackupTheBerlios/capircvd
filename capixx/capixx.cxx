
#include"capixx.hxx"
#include"capiobj.hxx"
#include"capiex.hxx"
#include"capimsg.hxx"

#include<map>

CAPIxx::CAPIxx(int maxChannels) {
	maxchans=maxChannels;
	capi=new CAPIobj();

	if(!capi->isinstalled()) 
		throw Ex("No CAPI/Controller installed!");

	int res=capi->capiregister(2,7,2048);

	//char *x="\x1e\x00\x02\x00\x05\x80\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

	CAPImsg *c=new CAPImsg();
	c->LISTEN_REQ(1,0,0,0,0,0,NULL,NULL);
	c->CAPI_CMSG_2_MESSAGE();
	capi->put_message(c->msg);
}

CAPIxx::~CAPIxx() {
	delete capi;
}

int CAPIxx::ProcessMessage() {

	unsigned char*MSG=NULL;
	return capi->get_message(&MSG);

	int x=1;
	unsigned long ncci=0;

	return 0;
}

