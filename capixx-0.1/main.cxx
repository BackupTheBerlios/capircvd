
#include"capixx.hxx"
#include"capiobj.hxx"
#include"capiex.hxx"

#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<iostream.h>

void main() {

	bool exit=false;
	CAPIxx *capi=new CAPIxx(2);

	while(!exit) {
		int res;
		res=capi->ProcessMessage();
		cout << res << endl;
#ifdef WIN32
		exit=(kbhit()!=0);
#else
		fd_set rfds;
		struct timeval tv;
		int retval;
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		tv.tv_sec = 1;
		tv.tv_usec = 1;
		retval = select(1, &rfds, NULL, NULL, &tv);
		exit=retval;
#endif
	}
	delete capi;
}

