#include"capiobj.hxx"
#include"capiex.hxx"

bool CAPIobj::isinstalled() {
	return Xcapi_installed()==0;
}

int CAPIobj::capiregister(_cdword maxLogicalConnection,
	_cdword maxDataBlocks, _cdword maxBDataLen) {
#ifdef WIN32
	int res=Xcapi_register((maxLogicalConnection+1)*1024,maxLogicalConnection,
		maxDataBlocks,maxBDataLen,&ApplId);
#else
	int res=Xcapi_register(maxLogicalConnection,maxDataBlocks,
		maxBDataLen,&ApplId);
#endif		
	return res;
}

int CAPIobj::release() {
	return Xcapi_release(ApplId);
}
int CAPIobj::operator>>(CAPImsg *Cmsg) {
	int res=get_cmessage((unsigned char **)&Cmsg->msg);
	if(res==0)
		Cmsg->CAPI_MESSAGE_2_CMSG();
	return res;
}

void CAPIobj::operator<<(CAPImsg *Cmsg) {
	Cmsg->cmsg->ApplId=ApplId;
	Cmsg->CAPI_CMSG_2_MESSAGE();
	put_cmessage(Cmsg->msg);
}

int CAPIobj::put_cmessage(void* pCAPIMessage) {
	return Xcapi_put_message(ApplId,pCAPIMessage);
}

int CAPIobj::get_cmessage(unsigned char** ppCAPIMesssage) {
	return Xcapi_get_message(ApplId,ppCAPIMesssage);
}

int CAPIobj::get_profile(_cdword Controller, void* SzBuffer) {
#ifdef WIN32
	return Xcapi_get_profile(SzBuffer,Controller);
#endif
#ifdef __linux__
	return Xcapi_get_profile(Controller,SzBuffer);
#endif
}

int CAPIobj::get_manufacturer(void* SzBuffer) {
	return Xcapi_get_manufacturer(SzBuffer);
}

int CAPIobj::get_version(_cdword* pCAPIMajor, _cdword* pCAPIMinor, _cdword* pManufacturerMajor, _cdword* pManufacturerMinor) {
	return Xcapi_get_version(pCAPIMajor,pCAPIMinor,pManufacturerMajor,pManufacturerMinor);
}

int CAPIobj::get_serial_number(void* SzBuffer) {
	return Xcapi_get_serial_number(SzBuffer);
}

CAPIobj::CAPIobj() {
#ifdef WIN32
	capidll=LoadLibrary("CAPI2032_debug.DLL");
#endif

#ifdef __linux__
	void* x;
	capidll=dlopen("libcapi20.so",RTLD_GLOBAL|RTLD_NOW);
#endif

#ifdef DEBUG
	cout << "capidll=0x" << hex << (int) capidll << endl;
#endif

	if(capidll==0) 
		throw Ex("CAPI-library (libcapi20.so) is not available!");

#ifdef WIN32

	Xcapi_installed=GetProcAddress(capidll,"CAPI_INSTALLED");
	Xcapi_register=(int (STDCALL *)(_cdword, _cdword, _cdword, _cdword,
		 _cword*))GetProcAddress(capidll,"CAPI_REGISTER");
	Xcapi_release=(int (STDCALL *)(_cdword))GetProcAddress(capidll,
		"CAPI_RELEASE");
	Xcapi_put_message=(int (STDCALL *)(_cdword, void*))GetProcAddress(
		capidll,"CAPI_PUT_MESSAGE");
	Xcapi_get_message=(int (STDCALL *)(_cdword, unsigned char* *))
		GetProcAddress(capidll,"CAPI_GET_MESSAGE");
        Xcapi_get_profile=(int (STDCALL *)(void*, _cdword))GetProcAddress
		(capidll,"CAPI_GET_PROFILE");
	Xcapi_get_manufacturer=(int (STDCALL *)(void*))GetProcAddress(capidll,
		"CAPI_GET_MANUFACTURER");
        Xcapi_get_version=(int (STDCALL *)(_cdword*, _cdword*, _cdword*,
		 _cdword *))GetProcAddress(capidll,"CAPI_GET_VERSION");
        Xcapi_get_serial_number=(int (STDCALL *)(void*))GetProcAddress(capidll,
		"CAPI_GET_SERIAL_NUMBER");
#endif
#ifdef __linux__
	Xcapi_installed=(int(*)())dlsym(capidll,"capi20_isinstalled");
	Xcapi_register=(int (STDCALL *)(_cdword, _cdword, _cdword, _cword*))
		dlsym(capidll,"capi20_register");
	Xcapi_release=(int (STDCALL *)(_cdword))dlsym(capidll,"capi20_release");
	Xcapi_put_message=(int (STDCALL *)(_cdword, void*))dlsym(capidll,
		"capi20_put_message");
	Xcapi_get_message=(int (STDCALL *)(_cdword, unsigned char* *))dlsym(
		capidll,"capi20_get_message");
	Xcapi_get_profile=(int (STDCALL *)(_cdword,void*))dlsym(capidll,
		"capi20_get_profile");
	Xcapi_get_manufacturer=(int (STDCALL *)(void*))dlsym(capidll,
		"capi20_get_manufacturer");
	Xcapi_get_version=(int (STDCALL *)(_cdword*, _cdword*, _cdword*,
		 _cdword *))dlsym(capidll,"capi20_get_version");
	Xcapi_get_serial_number=(int (STDCALL *)(void*))dlsym(capidll,
		"capi20_get_serial_number");
#endif

#ifdef DEBUG
	cout << "Addresses of CAPI-functions:" << endl <<
	"	capi_isinstalled=0x" << hex << (int)capi_installed << endl <<
	"	capi_register=0x" << hex << (int)Xcapi_register << endl <<
	"	capi_release=0x" << hex << (int)capi_release << endl <<
	"	capi_put_message=0x" << hex << (int)capi_put_message << endl <<
	"	capi_get_message=0x" << hex << (int)capi_get_message << endl <<
	"	capi_get_profile=0x" << hex << (int)capi_get_profile << endl <<
	"	capi_get_manufacturer=0x" << hex << (int)capi_get_manufacturer << endl <<
	"	capi_get_version=0x" << hex << (int)capi_get_version << endl <<
	"	capi_get_serial_number=0x" << hex << (int)capi_get_serial_number << endl;
#endif
	if(Xcapi_installed==0 || Xcapi_register==0 ||
		 Xcapi_release==0 || Xcapi_put_message==0 ||
		 Xcapi_get_message==0 || Xcapi_get_profile==0 ||
		 Xcapi_get_manufacturer==0 || Xcapi_get_version==0 ||
		 Xcapi_get_serial_number==0) 
		throw Ex("Some CAPI-functions are not available!");
}

CAPIobj::~CAPIobj() {
	release();
}




