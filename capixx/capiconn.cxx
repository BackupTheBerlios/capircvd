#include"capiconn.hxx"

CAPIConnection::CAPIConnection() {
}

CAPIConnection::~CAPIConnection() {
}

_cdword CAPIConnection::getNCCI() {
	return NCCI;
}

void CAPIConnection::connectind(CAPImsg *c) {
}

void CAPIConnection::disconnectind(CAPImsg *c) {
}


