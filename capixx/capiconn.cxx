#include"capiconn.hxx"
#include"capimsg.hxx"
#include<iostream.h>

CAPIConnection::CAPIConnection() {
}

CAPIConnection::CAPIConnection(CAPImsg *msg, CAPIobj *Capi) {

 cout << "New CAPIConnection" << endl;

 capi=Capi;
 if(msg->cmsg->Command==CAPI_CONNECT && msg->cmsg->Subcommand==CAPI_IND) {
  NCCI=msg->cmsg->adr.adrNCCI;
 }

// msg->CONNECT_RESP(0,0,NCCI,0,0,0,0,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

 msg->ALERT_REQ(0,0,NCCI,NULL,NULL,NULL,NULL);
 (*capi) << msg;

}

CAPIConnection::~CAPIConnection() {

 cout << "Deleted CAPIConnection" << endl;

}

_cdword CAPIConnection::getNCCI() {
	return NCCI;
}

void CAPIConnection::connectind(CAPImsg *c) {
}

void CAPIConnection::connectactiveind(CAPImsg *c) {
 c->CONNECT_ACTIVE_RESP(0,0,NCCI);
 (*capi) << c;
}

void CAPIConnection::disconnectind(CAPImsg *c) {
}


