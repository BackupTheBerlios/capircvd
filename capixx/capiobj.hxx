#ifndef CAPIobj_HXX
#define CAPIobj_HXX

#ifdef WIN32
#pragma warning(disable:4786)

#include<windows.h>
#include<conio.h>
#endif

#ifdef __linux__
#include<dlfcn.h>
#endif

#ifdef WIN32
 #define STDCALL __stdcall
#else
 #define STDCALL
#endif

#include"capimsg.hxx"

class CAPIobj {

private:

#ifdef WIN32
        HINSTANCE capidll;
#else
        void* capidll;
#endif
	_cword ApplId;

#ifdef WIN32
        int (STDCALL *Xcapi_register)(_cdword MessageBufferSize,
		_cdword maxLogicalConnection, _cdword maxDataBlocks,
		_cdword maxBDataLen, _cword *pApplID);
	int (STDCALL *Xcapi_get_profile)(void* SzBuffer, _cdword CtrlNr);
#else
        int (STDCALL *Xcapi_register)(_cdword maxLogicalConnection,
		_cdword maxDataBlocks, _cdword maxBDataLen, _cword *pApplID);
	int (STDCALL *Xcapi_get_profile)(_cdword CtrlNr, void* SzBuffer);
#endif
        int (STDCALL *Xcapi_installed)();
	int (STDCALL *Xcapi_release)(_cdword ApplID);
	int (STDCALL *Xcapi_put_message)(_cdword ApplID, void* pCAPIMessage);
	int (STDCALL *Xcapi_get_message)(_cdword ApplID,
		unsigned char* *ppCAPIMessage);
	int (STDCALL *Xcapi_get_manufacturer)(void* SzBuffer);
	int (STDCALL *Xcapi_get_version)(_cdword *pCAPIMajor,
		_cdword *pCAPIMinor, _cdword *pManufacturerMajor,
		_cdword *pManufacturerMinor);
	int (STDCALL *Xcapi_get_serial_number)(void* SzBuffer);

        int put_cmessage(void* pCAPIMessage);
        int get_cmessage(unsigned char** ppCAPIMessage);
public:

	bool isinstalled();
	int capiregister(_cdword maxLogicalConnection, _cdword maxDataBlocks, _cdword maxBDataLen);
        int release();

	void operator<<(CAPImsg *Cmsg);
	int operator>>(CAPImsg *Cmsg);

        int get_profile(_cdword Controller,void* SzBuffer);
        int get_manufacturer(void* SzBuffer);
        int get_version(_cdword *pCAPIMajor, _cdword *pCAPIMinor, _cdword *pManufacturerMajor, _cdword *pManufacturerMinor);
        int get_serial_number(void* SzBuffer);

	CAPIobj();
	~CAPIobj();
};

#endif
