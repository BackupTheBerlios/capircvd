
#include"capiobj.hxx"
#include"capiex.hxx"

#include<map>

class CAPIxx {

private:

	_cdword ApplId;
	CAPIobj *capi;
	unsigned int maxchans;

	//std::map<tNCCI,CAPIxxConnection*> connections;
	int incoming_unassigned;

public:
	CAPIxx(int maxChannels);
	~CAPIxx();
	int ProcessMessage();
};

