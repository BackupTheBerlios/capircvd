
#include"capixx.hxx"
#include"capiobj.hxx"
#include"capiex.hxx"
#include"capimsg.hxx"
#include"capiconn.hxx"

#include<map>
#include<iostream.h>

CAPIxx::CAPIxx(int maxChannels) {
	int ii;
	maxchans=maxChannels;

	if(! (capi.isinstalled())) 
		throw Ex("No CAPI/Controller installed!");

	capi_profile prof;
	capi.get_profile(0,&prof);

        unsigned char controller=prof.ncontroller;

        int bchans=0;
        for(ii=1;ii<=controller;ii++) {
		capi.get_profile(ii,&prof);
		bchans+=prof.nbchannel;
	}

	int res=capi.capiregister(bchans,7,2048);
	cout << res << endl;
	CAPImsg *c=new CAPImsg();
        for(ii=1;ii<=controller;ii++) {
		c->LISTEN_REQ(0,0,ii,0x03ff,0x1fff03ff,0,NULL,NULL);
		capi << c;
	}
	delete c;
}

CAPIxx::~CAPIxx() {
}

int CAPIxx::ProcessMessage() {

	CAPImsg *c=new CAPImsg();
	int res = capi >> c;
	if(res==0) {
		cout << hex << "Cmd: 0x" << (int)c->cmsg->Command << " SubCmd: 0x" << (int)c->cmsg->Subcommand << endl;
		switch(c->cmsg->Subcommand) {
		case CAPI_IND:
		 switch(c->cmsg->Command) {
			case CAPI_CONNECT:
				{
				cout << "CONNECT_IND NCCI=0x" << hex << c->cmsg->adr.adrNCCI << endl;
				CAPIConnection *conn;
				connections[c->cmsg->adr.adrNCCI]=conn=new CAPIConnection(c,&capi);
				}
			break;
			case CAPI_CONNECT_ACTIVE:
				cout << "CONNECT_ACTIVE_IND NCCI=0x" << hex << c->cmsg->adr.adrNCCI << endl;
				connections[c->cmsg->adr.adrNCCI]->connectactiveind(c);
			break;
			case CAPI_DISCONNECT:
				cout << "DISCONNECT_IND NCCI=0x" << hex << c->cmsg->adr.adrNCCI << endl;
				delete connections[c->cmsg->adr.adrNCCI];
			break;
			case CAPI_INFO:
				cout << "INFO_IND NCCI=0x" << hex << c->cmsg->adr.adrNCCI << " InfoNumber=0x" << c->cmsg->InfoNumber << endl;
			break;
		 }
		 break;
		case CAPI_RESP:
                 switch(c->cmsg->Command) {
                        case CAPI_LISTEN:
                                cout << "LISTEN_RESP NCCI=0x" << hex << c->cmsg->adr.adrNCCI << endl;
                        break;
                 }
		 break;
		}
	}
	return res;
}

