#include<iostream.h>
#include"capimsg.hxx"

#include<assert.h>
#include<string.h>

#define _CBYTE         1
#define _CWORD         2
#define _CDWORD        3
#define _CQWORD        4
#define _CSTRUCT       5
#define _CMSTRUCT      6
#define _CEND          7

#define byteTLcpy(x,y)        *(_cbyte *)(x)=*(_cbyte *)(y);
#define wordTLcpy(x,y)        *(_cword *)(x)=*(_cword *)(y);
#define dwordTLcpy(x,y)       memcpy(x,y,4);
#define structTLcpy(x,y,l)    memcpy (x,y,l)
#define structTLcpyovl(x,y,l) memmove (x,y,l)

#define byteTRcpy(x,y)        *(_cbyte *)(y)=*(_cbyte *)(x);
#define wordTRcpy(x,y)        *(_cword *)(y)=*(_cword *)(x);
#define dwordTRcpy(x,y)       memcpy(y,x,4);
#define structTRcpy(x,y,l)    memcpy (y,x,l)
#define structTRcpyovl(x,y,l) memmove (y,x,l)

#ifdef __linux__
#define qwordTLcpy(x,y)       memcpy(x,y,8);
#define qwordTRcpy(x,y)       memcpy(y,x,8);
#endif

#define TYP (cdef[cmsg->par[cmsg->p]].typ)
#define OFF (((char *)cmsg)+cdef[cmsg->par[cmsg->p]].off)

typedef struct {
    int typ;
    unsigned off;
} _cdef;

static _cdef cdef[] = {
    /*00*/{_CEND},
    /*01*/{_CEND},
    /*02*/{_CEND},
    /*03*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->adr.adrController},
    /*04*/{_CMSTRUCT,   (unsigned)(unsigned long)&((_cmsg *)0)->AdditionalInfo},
    /*05*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->B1configuration},
    /*06*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->B1protocol},
    /*07*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->B2configuration},
    /*08*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->B2protocol},
    /*09*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->B3configuration},
    /*0a*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->B3protocol},
    /*0b*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->BC},
    /*0c*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->BChannelinformation},
    /*0d*/{_CMSTRUCT,   (unsigned)(unsigned long)&((_cmsg *)0)->BProtocol},
    /*0e*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->CalledPartyNumber},
    /*0f*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->CalledPartySubaddress},
    /*10*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->CallingPartyNumber},
    /*11*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->CallingPartySubaddress},
    /*12*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->CIPmask},
    /*13*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->CIPmask2},
    /*14*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->CIPValue},
    /*15*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->Class},
    /*16*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->ConnectedNumber},
    /*17*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->ConnectedSubaddress},
#ifndef __linux__
    /*18*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->Data},
#else
    /*18*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->Data32},
#endif
    /*19*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->DataHandle},
    /*1a*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->DataLength},
    /*1b*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->FacilityConfirmationParameter},
    /*1c*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->Facilitydataarray},
    /*1d*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->FacilityIndicationParameter},
    /*1e*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->FacilityRequestParameter},
    /*1f*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->FacilityResponseParameters},
    /*20*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->FacilitySelector},
    /*21*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->Flags},
    /*22*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->Function},
    /*23*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->HLC},
    /*24*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->Info},
    /*25*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->InfoElement},
    /*26*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->InfoMask},
    /*27*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->InfoNumber},
    /*28*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->Keypadfacility},
    /*29*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->LLC},
    /*2a*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->ManuData},
    /*2b*/{_CDWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->ManuID},
    /*2c*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->NCPI},
    /*2d*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->Reason},
    /*2e*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->Reason_B3},
    /*2f*/{_CWORD,      (unsigned)(unsigned long)&((_cmsg *)0)->Reject},
    /*30*/{_CSTRUCT,    (unsigned)(unsigned long)&((_cmsg *)0)->Useruserdata},
#ifdef __linux__
    /*31*/{_CQWORD,     (unsigned)(unsigned long)&((_cmsg *)0)->Data64},
#endif
};

static unsigned char *cpars[] = {
    /*00*/ 0,
    /*01 ALERT_REQ*/            (unsigned char*)"\x03\x04\x0c\x28\x30\x1c\x01\x01",
    /*02 CONNECT_REQ*/          (unsigned char*)"\x03\x14\x0e\x10\x0f\x11\x0d\x06\x08\x0a\x05\x07\x09\x01\x0b\x29\x23\x04\x0c\x28\x30\x1c\x01\x01",
    /*03*/ 0,
    /*04 DISCONNECT_REQ*/       (unsigned char*)"\x03\x04\x0c\x28\x30\x1c\x01\x01",
    /*05 LISTEN_REQ*/           (unsigned char*)"\x03\x26\x12\x13\x10\x11\x01",
    /*06*/ 0,
    /*07*/ 0,
    /*08 INFO_REQ*/             (unsigned char*)"\x03\x0e\x04\x0c\x28\x30\x1c\x01\x01",
    /*09 FACILITY_REQ*/         (unsigned char*)"\x03\x20\x1e\x01",
    /*0a SELECT_B_PROTOCOL_REQ*/ (unsigned char*)"\x03\x0d\x06\x08\x0a\x05\x07\x09\x01\x01",
    /*0b CONNECT_B3_REQ*/       (unsigned char*)"\x03\x2c\x01",
    /*0c*/ 0,
    /*0d DISCONNECT_B3_REQ*/    (unsigned char*)"\x03\x2c\x01",
    /*0e*/ 0,
#ifndef __linux__
    /*0f DATA_B3_REQ*/          (unsigned char*)"\x03\x18\x1a\x19\x21\x01",
#else
    /*0f DATA_B3_REQ*/          (unsigned char*)"\x03\x18\x1a\x19\x21\x31\x01",
#endif
    /*10 RESET_B3_REQ*/         (unsigned char*)"\x03\x2c\x01",
    /*11*/ 0,
    /*12*/ 0,
    /*13 ALERT_CONF*/           (unsigned char*)"\x03\x24\x01",
    /*14 CONNECT_CONF*/         (unsigned char*)"\x03\x24\x01",
    /*15*/ 0,
    /*16 DISCONNECT_CONF*/      (unsigned char*)"\x03\x24\x01",
    /*17 LISTEN_CONF*/          (unsigned char*)"\x03\x24\x01",
    /*18 MANUFACTURER_REQ*/     (unsigned char*)"\x03\x2b\x15\x22\x2a\x01",
    /*19*/ 0,
    /*1a INFO_CONF*/            (unsigned char*)"\x03\x24\x01",
    /*1b FACILITY_CONF*/        (unsigned char*)"\x03\x24\x20\x1b\x01",
    /*1c SELECT_B_PROTOCOL_CONF*/ (unsigned char*)"\x03\x24\x01",
    /*1d CONNECT_B3_CONF*/      (unsigned char*)"\x03\x24\x01",
    /*1e*/ 0,
    /*1f DISCONNECT_B3_CONF*/   (unsigned char*)"\x03\x24\x01",
    /*20*/ 0,
    /*21 DATA_B3_CONF*/         (unsigned char*)"\x03\x19\x24\x01",
    /*22 RESET_B3_CONF*/        (unsigned char*)"\x03\x24\x01",
    /*23*/ 0,
    /*24*/ 0,
    /*25*/ 0,
    /*26 CONNECT_IND*/          (unsigned char*)"\x03\x14\x0e\x10\x0f\x11\x0b\x29\x23\x04\x0c\x28\x30\x1c\x01\x01",
    /*27 CONNECT_ACTIVE_IND*/   (unsigned char*)"\x03\x16\x17\x29\x01",
    /*28 DISCONNECT_IND*/       (unsigned char*)"\x03\x2d\x01",
    /*29*/ 0,
    /*2a MANUFACTURER_CONF*/    (unsigned char*)"\x03\x2b\x15\x22\x2a\x01",
    /*2b*/ 0,
    /*2c INFO_IND*/             (unsigned char*)"\x03\x27\x25\x01",
    /*2d FACILITY_IND*/         (unsigned char*)"\x03\x20\x1d\x01",
    /*2e*/ 0,
    /*2f CONNECT_B3_IND*/       (unsigned char*)"\x03\x2c\x01",
    /*30 CONNECT_B3_ACTIVE_IND*/ (unsigned char*)"\x03\x2c\x01",
    /*31 DISCONNECT_B3_IND*/    (unsigned char*)"\x03\x2e\x2c\x01",
    /*32*/ 0,
#ifndef __linux__
    /*33 DATA_B3_IND*/          (unsigned char*)"\x03\x18\x1a\x19\x21\x01",
#else
    /*33 DATA_B3_IND*/          (unsigned char*)"\x03\x18\x1a\x19\x21\x31\x01",
#endif
    /*34 RESET_B3_IND*/         (unsigned char*)"\x03\x2c\x01",
    /*35 CONNECT_B3_T90_ACTIVE_IND*/ (unsigned char*)"\x03\x2c\x01",
    /*36*/ 0,
    /*37*/ 0,
    /*38 CONNECT_RESP*/         (unsigned char*)"\x03\x2f\x0d\x06\x08\x0a\x05\x07\x09\x01\x16\x17\x29\x04\x0c\x28\x30\x1c\x01\x01",
    /*39 CONNECT_ACTIVE_RESP*/  (unsigned char*)"\x03\x01",
    /*3a DISCONNECT_RESP*/      (unsigned char*)"\x03\x01",
    /*3b*/ 0,
    /*3c MANUFACTURER_IND*/     (unsigned char*)"\x03\x2b\x15\x22\x2a\x01",
    /*3d*/ 0,
    /*3e INFO_RESP*/            (unsigned char*)"\x03\x01",
    /*3f FACILITY_RESP*/        (unsigned char*)"\x03\x20\x1f\x01",
    /*40*/ 0,
    /*41 CONNECT_B3_RESP*/      (unsigned char*)"\x03\x2f\x2c\x01",
    /*42 CONNECT_B3_ACTIVE_RESP*/ (unsigned char*)"\x03\x01",
    /*43 DISCONNECT_B3_RESP*/   (unsigned char*)"\x03\x01",
    /*44*/ 0,
    /*45 DATA_B3_RESP*/         (unsigned char*)"\x03\x19\x01",
    /*46 RESET_B3_RESP*/        (unsigned char*)"\x03\x01",
    /*47 CONNECT_B3_T90_ACTIVE_RESP*/ (unsigned char*)"\x03\x01",
    /*48*/ 0,
    /*49*/ 0,
    /*4a*/ 0,
    /*4b*/ 0,
    /*4c*/ 0,
    /*4d*/ 0,
    /*4e MANUFACTURER_RESP*/    (unsigned char*)"\x03\x2b\x15\x22\x2a\x01",
};

static unsigned command_2_index (unsigned c, unsigned sc) {
    if (c & 0x80) c = 0x9+(c&0x0f);
    else if (c<=0x0f) ;
    else if (c==0x41) c = 0x9+0x1;
    else if (c==0xff) c = 0x00;
    return (sc&3)*(0x9+0x9)+c;
}

static void jumpcstruct (_cmsg *cmsg) {
    unsigned layer;
    for (cmsg->p++,layer=1; layer;) {
        assert (cmsg->p);
        cmsg->p++;
        switch (TYP) {
            case _CMSTRUCT:
                layer++;
                break;
            case _CEND:
                layer--;
                break;
        }
    }
}

static void MESSAGE_2_PARS (_cmsg *cmsg) {
    for (;TYP != _CEND; cmsg->p++) {

        switch (TYP) {
            case _CBYTE:
                byteTRcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l++;
                break;
            case _CWORD:
                wordTRcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l+=2;
                break;
            case _CDWORD:
                dwordTRcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l+=4;
                break;
#ifdef __linux__
            case _CQWORD:
                qwordTRcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l+=8;
                break;
#endif
            case _CSTRUCT:
                *(CAPI_MESSAGE *)OFF = cmsg->m+cmsg->l;

                if (cmsg->m[cmsg->l] != 0xff)
                    cmsg->l+= 1+ cmsg->m[cmsg->l];
                else
                    cmsg->l+= 3+ *(_cword *)(cmsg->m+cmsg->l+1);
                break;
            case _CMSTRUCT:
                /*----- Metastruktur 0 -----*/
                if (cmsg->m[cmsg->l] == '\0') {
                    *(_cmstruct *)OFF = CAPI_DEFAULT;
                    cmsg->l++;
                    jumpcstruct (cmsg);
                }
                else {
                    unsigned _l = cmsg->l;
                    *(_cmstruct *)OFF = CAPI_COMPOSE;
                    cmsg->l = (cmsg->m+_l)[0] == 255 ? cmsg->l+3 : cmsg->l+1;
                    cmsg->p++;
                    MESSAGE_2_PARS (cmsg);
                }
                break;
        }
    }
}
	
static void PARS_2_MESSAGE (_cmsg *cmsg) {

    for (;TYP != _CEND; cmsg->p++) {
        switch (TYP) {
            case _CBYTE:
                byteTLcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l++;
                break;
            case _CWORD:
                wordTLcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l+=2;
                break;
            case _CDWORD:
                dwordTLcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l+=4;
                break;
#ifdef __linux__
            case _CQWORD:
                qwordTLcpy (cmsg->m+cmsg->l, OFF);
                cmsg->l+=8;
                break;
#endif
            case _CSTRUCT:
                if (*(CAPI_MESSAGE *) OFF == 0) {
                    *(cmsg->m+cmsg->l)='\0';
                    cmsg->l++;
                }
                else if(**(_cstruct *)OFF != 0xff) {
                    structTLcpy (cmsg->m+cmsg->l, *(_cstruct *)OFF, 1+**(_cstruct *)OFF);
                    cmsg->l+=1+**(_cstruct *)OFF;
                }
                else {
                    _cstruct s = *(_cstruct *)OFF;
                    structTLcpy (cmsg->m+cmsg->l, s, 3+*(_cword *)(s+1));
                    cmsg->l+= 3+*(_cword *)(s+1);
                }
                break;
            case _CMSTRUCT:
                /*----- Metastruktur 0 -----*/
                if (*(_cmstruct *)OFF == CAPI_DEFAULT) {
                    *(cmsg->m+cmsg->l)='\0';
                    cmsg->l++;
                    jumpcstruct (cmsg);
                }
                /*----- Metastruktur wird composed -----*/
                else {
                    unsigned _l = cmsg->l;
                    unsigned _ls;
                    cmsg->l++;
                    cmsg->p++;
                    PARS_2_MESSAGE (cmsg);
                    _ls = cmsg->l-_l-1;
                    if (_ls < 255)
                        (cmsg->m+_l)[0] = (_cbyte)_ls;
                    else {
                        structTLcpyovl (cmsg->m+_l+3, cmsg->m+_l+1, _ls);
                        (cmsg->m+_l)[0] = 0xff;
                        wordTLcpy (cmsg->m+_l+1, &_ls);
                        cmsg->l+=2;
                    }
                }
                break;
        }
    }
}

unsigned CAPImsg::capi_cmsg_header (unsigned _ApplId,
                                 _cbyte _Command, _cbyte _Subcommand,
                                 _cword _Messagenumber, _cdword _Controller) {
    memset (cmsg, 0, sizeof(_cmsg));
    cmsg->ApplId = _ApplId ;
    cmsg->Command = _Command ;
    cmsg->Subcommand = _Subcommand ;
    cmsg->Messagenumber = _Messagenumber;
    cmsg->adr.adrController = _Controller ;
    return 0;
}

unsigned CAPImsg::CAPI_MESSAGE_2_CMSG () {
    memset (cmsg, 0, sizeof(_cmsg));
    cmsg->m = msg;
    cmsg->l = 8;
    cmsg->p = 0;
    byteTRcpy (cmsg->m+4, &cmsg->Command);
    byteTRcpy (cmsg->m+5, &cmsg->Subcommand);
    cmsg->par = cpars [command_2_index (cmsg->Command,cmsg->Subcommand)];

    MESSAGE_2_PARS (cmsg);

#ifdef __linux__
    if (   cmsg->Command == CAPI_DATA_B3
        && (cmsg->Subcommand == CAPI_REQ || cmsg->Subcommand == CAPI_IND)) {
       if (sizeof(void *) == 4) {
          cmsg->Data = (unsigned char *) cmsg->Data32;
       } else {
          cmsg->Data = (unsigned char *) cmsg->Data64;
       }
    }
#endif

    wordTRcpy (msg+0, &cmsg->l);
    wordTRcpy (cmsg->m+2, &cmsg->ApplId);
    wordTRcpy (cmsg->m+6, &cmsg->Messagenumber);

    msg=NULL;

    return 0;
}

unsigned CAPImsg::CAPI_CMSG_2_MESSAGE () {
    msg=msgtmp;
    cmsg->m = msg;
    cmsg->l = 8;
    cmsg->p = 0;
    cmsg->par = cpars [command_2_index (cmsg->Command,cmsg->Subcommand)];

#ifdef __linux__
    if (   cmsg->Command == CAPI_DATA_B3
        && (cmsg->Subcommand == CAPI_REQ || cmsg->Subcommand == CAPI_IND)) {
       if (sizeof(void *) == 4) {
          cmsg->Data32 = (_cdword) cmsg->Data;
          cmsg->Data64 = 0;
       } else {
          cmsg->Data32 = 0;
          cmsg->Data64 = (_cqword) cmsg->Data;
       }
    }
#endif

    PARS_2_MESSAGE (cmsg);

    wordTLcpy (msg+0, &cmsg->l);
    byteTLcpy (cmsg->m+4, &cmsg->Command);
    byteTLcpy (cmsg->m+5, &cmsg->Subcommand);
    wordTLcpy (cmsg->m+2, &cmsg->ApplId);
    wordTLcpy (cmsg->m+6, &cmsg->Messagenumber);

    return 0;
}

CAPImsg::CAPImsg() {
		cmsg=new _cmsg;
		msgtmp=new _cbyte[2048];
		msg=msgtmp;
		memset (cmsg, 0, sizeof(_cmsg));
	}

CAPImsg::~CAPImsg() {
		delete msgtmp;
		}

CAPImsg::CAPImsg(_cword applid, _cword msgtype,_cword msgnumber) {
		cmsg=new _cmsg;
		memset (cmsg, 0, sizeof(_cmsg));
		cmsg->ApplId = applid ;
		cmsg->Command = msgtype>>8;
		cmsg->Subcommand = msgtype&0xff;
		cmsg->Messagenumber = msgnumber;
	//	cmsg->adr.adrController = _Controller ;
        }

CAPImsg::CAPImsg(_cword applid, _cbyte cmd,_cbyte scmd,_cword msgnumber) {
		cmsg=new _cmsg;
		memset (cmsg, 0, sizeof(_cmsg));
		cmsg->ApplId = applid ;
		cmsg->Command = cmd;
		cmsg->Subcommand = scmd;
		cmsg->Messagenumber = msgnumber;
	//	cmsg->adr.adrController = _Controller ;
        }

void CAPImsg::CONNECT_B3_REQ(_cword ApplId, _cword Messagenumber,
					    _cdword adr,
					    _cstruct NCPI)
{
	capi_cmsg_header(ApplId, 0x82, 0x80, Messagenumber, adr);
	cmsg->NCPI = NCPI;
}

void CAPImsg::FACILITY_REQ(_cword ApplId, _cword Messagenumber,
					  _cdword adr,
					  _cword FacilitySelector,
				       _cstruct FacilityRequestParameter)
{
	capi_cmsg_header(ApplId, 0x80, 0x80, Messagenumber, adr);
	cmsg->FacilitySelector = FacilitySelector;
	cmsg->FacilityRequestParameter = FacilityRequestParameter;
}

void CAPImsg::INFO_REQ(_cword ApplId, _cword Messagenumber,
				      _cdword adr,
				      _cstruct CalledPartyNumber,
				      _cstruct BChannelinformation,
				      _cstruct Keypadfacility,
				      _cstruct Useruserdata,
				      _cstruct Facilitydataarray)
{
	capi_cmsg_header(ApplId, 0x08, 0x80, Messagenumber, adr);
	cmsg->CalledPartyNumber = CalledPartyNumber;
	cmsg->BChannelinformation = BChannelinformation;
	cmsg->Keypadfacility = Keypadfacility;
	cmsg->Useruserdata = Useruserdata;
	cmsg->Facilitydataarray = Facilitydataarray;
}

void CAPImsg::LISTEN_REQ(_cword ApplId, _cword Messagenumber,
					_cdword adr,
					_cdword InfoMask,
					_cdword CIPmask,
					_cdword CIPmask2,
					_cstruct CallingPartyNumber,
					_cstruct CallingPartySubaddress)
{
	capi_cmsg_header(ApplId, 0x05, 0x80, Messagenumber, adr);
	cmsg->InfoMask = InfoMask;
	cmsg->CIPmask = CIPmask;
	cmsg->CIPmask2 = CIPmask2;
	cmsg->CallingPartyNumber = CallingPartyNumber;
	cmsg->CallingPartySubaddress = CallingPartySubaddress;
}

void CAPImsg::ALERT_REQ(_cword ApplId, _cword Messagenumber,
				       _cdword adr,
				       _cstruct BChannelinformation,
				       _cstruct Keypadfacility,
				       _cstruct Useruserdata,
				       _cstruct Facilitydataarray)
{
	capi_cmsg_header(ApplId, 0x01, 0x80, Messagenumber, adr);
	cmsg->BChannelinformation = BChannelinformation;
	cmsg->Keypadfacility = Keypadfacility;
	cmsg->Useruserdata = Useruserdata;
	cmsg->Facilitydataarray = Facilitydataarray;
}

void CAPImsg::CONNECT_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cword CIPValue,
					 _cstruct CalledPartyNumber,
					 _cstruct CallingPartyNumber,
					 _cstruct CalledPartySubaddress,
					 _cstruct CallingPartySubaddress,
					 _cword B1protocol,
					 _cword B2protocol,
					 _cword B3protocol,
					 _cstruct B1configuration,
					 _cstruct B2configuration,
					 _cstruct B3configuration,
					 _cstruct BC,
					 _cstruct LLC,
					 _cstruct HLC,
					 _cstruct BChannelinformation,
					 _cstruct Keypadfacility,
					 _cstruct Useruserdata,
					 _cstruct Facilitydataarray)
{

	capi_cmsg_header(ApplId, 0x02, 0x80, Messagenumber, adr);
	cmsg->CIPValue = CIPValue;
	cmsg->CalledPartyNumber = CalledPartyNumber;
	cmsg->CallingPartyNumber = CallingPartyNumber;
	cmsg->CalledPartySubaddress = CalledPartySubaddress;
	cmsg->CallingPartySubaddress = CallingPartySubaddress;
	cmsg->B1protocol = B1protocol;
	cmsg->B2protocol = B2protocol;
	cmsg->B3protocol = B3protocol;
	cmsg->B1configuration = B1configuration;
	cmsg->B2configuration = B2configuration;
	cmsg->B3configuration = B3configuration;
	cmsg->BC = BC;
	cmsg->LLC = LLC;
	cmsg->HLC = HLC;
	cmsg->BChannelinformation = BChannelinformation;
	cmsg->Keypadfacility = Keypadfacility;
	cmsg->Useruserdata = Useruserdata;
	cmsg->Facilitydataarray = Facilitydataarray;
}

void CAPImsg::DATA_B3_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 unsigned char *Data,
					 _cword DataLength,
					 _cword DataHandle,
					 _cword Flags)
{

	capi_cmsg_header(ApplId, 0x86, 0x80, Messagenumber, adr);
	cmsg->Data = Data;
	cmsg->DataLength = DataLength;
	cmsg->DataHandle = DataHandle;
	cmsg->Flags = Flags;
}

void CAPImsg::DISCONNECT_REQ(_cword ApplId, _cword Messagenumber,
					    _cdword adr,
					    _cstruct BChannelinformation,
					    _cstruct Keypadfacility,
					    _cstruct Useruserdata,
					    _cstruct Facilitydataarray)
{

	capi_cmsg_header(ApplId, 0x04, 0x80, Messagenumber, adr);
	cmsg->BChannelinformation = BChannelinformation;
	cmsg->Keypadfacility = Keypadfacility;
	cmsg->Useruserdata = Useruserdata;
	cmsg->Facilitydataarray = Facilitydataarray;
}

void CAPImsg::DISCONNECT_B3_REQ(_cword ApplId, _cword Messagenumber,
					       _cdword adr,
					       _cstruct NCPI)
{

	capi_cmsg_header(ApplId, 0x84, 0x80, Messagenumber, adr);
	cmsg->NCPI = NCPI;
}

void CAPImsg::MANUFACTURER_REQ(_cword ApplId, _cword Messagenumber,
					      _cdword adr,
					      _cdword ManuID,
					      _cdword Class,
					      _cdword Function,
					      _cstruct ManuData)
{

	capi_cmsg_header(ApplId, 0xff, 0x80, Messagenumber, adr);
	cmsg->ManuID = ManuID;
	cmsg->Class = Class;
	cmsg->Function = Function;
	cmsg->ManuData = ManuData;
}

void CAPImsg::RESET_B3_REQ(_cword ApplId, _cword Messagenumber,
					  _cdword adr,
					  _cstruct NCPI)
{

	capi_cmsg_header(ApplId, 0x87, 0x80, Messagenumber, adr);
	cmsg->NCPI = NCPI;
}

void CAPImsg::SELECT_B_PROTOCOL_REQ(_cword ApplId, _cword Messagenumber,
						   _cdword adr,
						   _cword B1protocol,
						   _cword B2protocol,
						   _cword B3protocol,
						_cstruct B1configuration,
						_cstruct B2configuration,
						_cstruct B3configuration)
{

	capi_cmsg_header(ApplId, 0x41, 0x80, Messagenumber, adr);
	cmsg->B1protocol = B1protocol;
	cmsg->B2protocol = B2protocol;
	cmsg->B3protocol = B3protocol;
	cmsg->B1configuration = B1configuration;
	cmsg->B2configuration = B2configuration;
	cmsg->B3configuration = B3configuration;
}

void CAPImsg::CONNECT_RESP(_cword ApplId, _cword Messagenumber,
					  _cdword adr,
					  _cword Reject,
					  _cword B1protocol,
					  _cword B2protocol,
					  _cword B3protocol,
					  _cstruct B1configuration,
					  _cstruct B2configuration,
					  _cstruct B3configuration,
					  _cstruct ConnectedNumber,
					  _cstruct ConnectedSubaddress,
					  _cstruct LLC,
					  _cstruct BChannelinformation,
					  _cstruct Keypadfacility,
					  _cstruct Useruserdata,
					  _cstruct Facilitydataarray)
{
	capi_cmsg_header(ApplId, 0x02, 0x83, Messagenumber, adr);
	cmsg->Reject = Reject;
	cmsg->B1protocol = B1protocol;
	cmsg->B2protocol = B2protocol;
	cmsg->B3protocol = B3protocol;
	cmsg->B1configuration = B1configuration;
	cmsg->B2configuration = B2configuration;
	cmsg->B3configuration = B3configuration;
	cmsg->ConnectedNumber = ConnectedNumber;
	cmsg->ConnectedSubaddress = ConnectedSubaddress;
	cmsg->LLC = LLC;
	cmsg->BChannelinformation = BChannelinformation;
	cmsg->Keypadfacility = Keypadfacility;
	cmsg->Useruserdata = Useruserdata;
	cmsg->Facilitydataarray = Facilitydataarray;
}

void CAPImsg::CONNECT_ACTIVE_RESP(_cword ApplId, _cword Messagenumber,
						 _cdword adr)
{

	capi_cmsg_header(ApplId, 0x03, 0x83, Messagenumber, adr);
}

void CAPImsg::CONNECT_B3_ACTIVE_RESP(_cword ApplId, _cword Messagenumber,
						    _cdword adr)
{

	capi_cmsg_header(ApplId, 0x83, 0x83, Messagenumber, adr);
}

void CAPImsg::CONNECT_B3_RESP(_cword ApplId, _cword Messagenumber,
					     _cdword adr,
					     _cword Reject,
					     _cstruct NCPI)
{
	capi_cmsg_header(ApplId, 0x82, 0x83, Messagenumber, adr);
	cmsg->Reject = Reject;
	cmsg->NCPI = NCPI;
}

void CAPImsg::CONNECT_B3_T90_ACTIVE_RESP(_cword ApplId, _cword Messagenumber,
							_cdword adr)
{

	capi_cmsg_header(ApplId, 0x88, 0x83, Messagenumber, adr);
}

void CAPImsg::DATA_B3_RESP(_cword ApplId, _cword Messagenumber,
					  _cdword adr,
					  _cword DataHandle)
{

	capi_cmsg_header(ApplId, 0x86, 0x83, Messagenumber, adr);
	cmsg->DataHandle = DataHandle;
}

void CAPImsg::DISCONNECT_B3_RESP(_cword ApplId, _cword Messagenumber,
						_cdword adr)
{

	capi_cmsg_header(ApplId, 0x84, 0x83, Messagenumber, adr);
}

void CAPImsg::DISCONNECT_RESP(_cword ApplId, _cword Messagenumber,
					     _cdword adr)
{

	capi_cmsg_header(ApplId, 0x04, 0x83, Messagenumber, adr);
}

void CAPImsg::FACILITY_RESP(_cword ApplId, _cword Messagenumber,
					   _cdword adr,
					   _cword FacilitySelector)
{

	capi_cmsg_header(ApplId, 0x80, 0x83, Messagenumber, adr);
	cmsg->FacilitySelector = FacilitySelector;
}

void CAPImsg::INFO_RESP(_cword ApplId, _cword Messagenumber,
				       _cdword adr)
{

	capi_cmsg_header(ApplId, 0x08, 0x83, Messagenumber, adr);
}

void CAPImsg::MANUFACTURER_RESP(_cword ApplId, _cword Messagenumber,
					       _cdword adr,
					       _cdword ManuID,
					       _cdword Class,
					       _cdword Function,
					       _cstruct ManuData)
{

	capi_cmsg_header(ApplId, 0xff, 0x83, Messagenumber, adr);
	cmsg->ManuID = ManuID;
	cmsg->Class = Class;
	cmsg->Function = Function;
	cmsg->ManuData = ManuData;
}

void CAPImsg::RESET_B3_RESP(_cword ApplId, _cword Messagenumber,
					   _cdword adr)
{

	capi_cmsg_header(ApplId, 0x87, 0x83, Messagenumber, adr);
}

