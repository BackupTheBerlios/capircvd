
#include"capimsg.hxx"
#include"capiobj.hxx"
#include"capiex.hxx"
#include"capiconn.hxx"

#include<map>

class CAPIxx {

private:

	CAPIobj capi;

	_cdword ApplId;
	unsigned int maxchans;

//	std::map<_cdword,CAPIConnection*> connections;
	int incoming_unassigned;

public:
	CAPIxx(int maxChannels);
	~CAPIxx();
	int ProcessMessage();
};

