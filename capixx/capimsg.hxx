#ifndef CAPIMSG_H
#define CAPIMSG_H

#define UNUSED__ALERT_CONF              0x0181
#define UNUSED__ALERT_REQ               0x0180
#define UNUSED__CONNECT_ACTIVE_IND      0x0382
#define UNUSED__CONNECT_ACTIVE_RESP     0x0383
#define UNUSED__CONNECT_B3_ACTIVE_IND   0x8382
#define UNUSED__CONNECT_B3_ACTIVE_RESP  0x8383
#define UNUSED__CONNECT_B3_CONF         0x8281
#define UNUSED__CONNECT_B3_IND          0x8282
#define UNUSED__CONNECT_B3_REQ          0x8280
#define UNUSED__CONNECT_B3_RESP         0x8283
#define UNUSED__CONNECT_B3_T90_ACTIVE_IND       0x8882
#define UNUSED__CONNECT_B3_T90_ACTIVE_RESP      0x8883
#define UNUSED__CONNECT_CONF            0x0281
#define UNUSED__CONNECT_IND             0x0282
#define UNUSED__CONNECT_REQ             0x0280
#define UNUSED__CONNECT_RESP            0x0283
#define UNUSED__DATA_B3_CONF            0x8681
#define UNUSED__DATA_B3_IND             0x8682
#define UNUSED__DATA_B3_REQ             0x8680
#define UNUSED__DATA_B3_RESP            0x8683
#define UNUSED__DISCONNECT_B3_CONF      0x8481
#define UNUSED__DISCONNECT_B3_IND       0x8482
#define UNUSED__DISCONNECT_B3_REQ       0x8480
#define UNUSED__DISCONNECT_B3_RESP      0x8483
#define UNUSED__DISCONNECT_CONF         0x0481
#define UNUSED__DISCONNECT_IND          0x0482
#define UNUSED__DISCONNECT_REQ          0x0480
#define UNUSED__DISCONNECT_RESP         0x0483
#define UNUSED__FACILITY_CONF           0x8081
#define UNUSED__FACILITY_IND            0x8082
#define UNUSED__FACILITY_REQ            0x8080
#define UNUSED__FACILITY_RESP           0x8083
#define UNUSED__INFO_CONF               0x0881
#define UNUSED__INFO_IND                0x0882
#define UNUSED__INFO_REQ                0x0880
#define UNUSED__INFO_RESP               0x0883
#define UNUSED__LISTEN_CONF             0x0581
#define UNUSED__LISTEN_REQ              0x0580
#define UNUSED__MANUFACTURER_CONF       0xff81
#define UNUSED__MANUFACTURER_IND        0xff82
#define UNUSED__MANUFACTURER_REQ        0xff80
#define UNUSED__MANUFACTURER_RESP       0xff83
#define UNUSED__RESET_B3_CONF           0x8781
#define UNUSED__RESET_B3_IND            0x8782
#define UNUSED__RESET_B3_REQ            0x8780
#define UNUSED__RESET_B3_RESP           0x8783
#define UNUSED__SELECT_B_PROTOCOL_CONF  0x4181
#define UNUSED__SELECT_B_PROTOCOL_REQ   0x4180

/*----- CAPI commands -----*/

#define CAPI_ALERT                  0x01
#define CAPI_CONNECT                0x02
#define CAPI_CONNECT_ACTIVE         0x03
#define CAPI_CONNECT_B3_ACTIVE      0x83
#define CAPI_CONNECT_B3             0x82
#define CAPI_CONNECT_B3_T90_ACTIVE  0x88
#define CAPI_DATA_B3                0x86
#define CAPI_DISCONNECT_B3          0x84
#define CAPI_DISCONNECT             0x04
#define CAPI_FACILITY               0x80
#define CAPI_INFO                   0x08
#define CAPI_LISTEN                 0x05
#define CAPI_MANUFACTURER           0xff
#define CAPI_RESET_B3               0x87
#define CAPI_SELECT_B_PROTOCOL      0x41

/*----- CAPI subcommands -----*/

#define CAPI_REQ    0x80
#define CAPI_CONF   0x81
#define CAPI_IND    0x82
#define CAPI_RESP   0x83


#define CAPI_REGISTER_ERROR     unsigned
#define MESSAGE_EXCHANGE_ERROR  unsigned

typedef unsigned char *CAPI_MESSAGE;

#if defined(__GLIBC__) && defined(__GLIBC_MINOR__)
#if (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 1) || __GLIBC__ > 2
#define HAS_UINT8_T
#endif
#endif

#ifdef HAS_UINT8_t
typedef uint8_t   _cbyte;
typedef uint16_t  _cword;
typedef uint32_t  _cdword;
typedef uint64_t  _cqword;
#else
typedef unsigned char      _cbyte;
typedef unsigned short     _cword;
typedef unsigned long      _cdword;
#ifdef WIN32
#include<windows.h>
typedef LONGLONG _cqword;
#else
typedef unsigned long long _cqword;
#endif
#endif

typedef CAPI_MESSAGE   _cstruct;
typedef enum { CAPI_COMPOSE = 0, CAPI_DEFAULT = 1 } _cmstruct;

typedef struct {
        /* Header */
        _cword ApplId;
        _cbyte Command;
        _cbyte Subcommand;
        _cword Messagenumber;

        /* Parameter */
        union {
                _cdword adrController;
                _cdword adrPLCI;
                _cdword adrNCCI;
        } adr;

        _cmstruct AdditionalInfo;
        _cstruct B1configuration;
        _cword B1protocol;
        _cstruct B2configuration;
        _cword B2protocol;
        _cstruct B3configuration;
        _cword B3protocol;
        _cstruct BC;
        _cstruct BChannelinformation;
        _cmstruct BProtocol;
        _cstruct CalledPartyNumber;
        _cstruct CalledPartySubaddress;
        _cstruct CallingPartyNumber;
        _cstruct CallingPartySubaddress;
        _cdword CIPmask;
        _cdword CIPmask2;
        _cword CIPValue;
        _cdword Class;
        _cstruct ConnectedNumber;
        _cstruct ConnectedSubaddress;
        _cdword Data32;
        _cqword Data64;
        _cword DataHandle;
        _cword DataLength;
        _cstruct FacilityConfirmationParameter;
        _cstruct Facilitydataarray;
        _cstruct FacilityIndicationParameter;
        _cstruct FacilityRequestParameter;
        _cstruct FacilityResponseParameters;
        _cword FacilitySelector;
        _cword Flags;
        _cdword Function;
        _cstruct HLC;
        _cword Info;
        _cstruct InfoElement;
        _cdword InfoMask;
        _cword InfoNumber;
        _cstruct Keypadfacility;
        _cstruct LLC;
        _cstruct ManuData;
        _cdword ManuID;
        _cstruct NCPI;
        _cword Reason;
        _cword Reason_B3;
        _cword Reject;
        _cstruct Useruserdata;
        unsigned char *Data;

        /* intern */
        unsigned l, p;
        unsigned char *par;
        _cbyte *m;

        /* buffer to construct message */
        _cbyte buf[180];

} _cmsg;

typedef struct capi_profile {
        _cword ncontroller;      /* number of installed controller */
        _cword nbchannel;        /* number of B-Channels */
        _cdword goptions;         /* global options */
        _cdword support1;         /* B1 protocols support */
        _cdword support2;         /* B2 protocols support */
        _cdword support3;         /* B3 protocols support */
        _cdword reserved[6];      /* reserved */
        _cdword manu[5];          /* manufacturer specific information */
} capi_profile;



class CAPImsg {


// private:

public:
        _cbyte *msg,*msgtmp;
        _cmsg *cmsg;

	unsigned int capi_cmsg_header(unsigned int, unsigned char,
					unsigned char, short unsigned int,
					long unsigned int);
	unsigned CAPImsg::CAPI_MESSAGE_2_CMSG();
	unsigned CAPImsg::CAPI_CMSG_2_MESSAGE();
	
	CAPImsg();
	~CAPImsg();

        CAPImsg(_cword applid, _cword msgtype,_cword msgnumber);
        CAPImsg(_cword applid, _cbyte cmd,_cbyte scmd,_cword msgnumber);

	void CONNECT_B3_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cstruct NCPI);

	void FACILITY_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cword FacilitySelector,
					 _cstruct FacilityRequestParameter);

	void INFO_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cstruct CalledPartyNumber,
					 _cstruct BChannelinformation,
					 _cstruct Keypadfacility,
					 _cstruct Useruserdata,
					 _cstruct Facilitydataarray);

	void LISTEN_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cdword InfoMask,
					 _cdword CIPmask,
					 _cdword CIPmask2,
					 _cstruct CallingPartyNumber,
					 _cstruct CallingPartySubaddress);

	void ALERT_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cstruct BChannelinformation,
					 _cstruct Keypadfacility,
					 _cstruct Useruserdata,
					 _cstruct Facilitydataarray);

	void CONNECT_REQ(_cword ApplId, _cword Messagenumber,
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
                                         _cstruct Facilitydataarray);

	void DATA_B3_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 unsigned char *Data,
					 _cword DataLength,
                                         _cword DataHandle,
                                         _cword Flags);

	void DISCONNECT_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cstruct BChannelinformation,
					 _cstruct Keypadfacility,
                                         _cstruct Useruserdata,
                                         _cstruct Facilitydataarray);

	void DISCONNECT_B3_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cstruct NCPI);

	void MANUFACTURER_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cdword ManuID,
					 _cdword Class,
                                         _cdword Function,
                                         _cstruct ManuData);

	void RESET_B3_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cstruct NCPI);

	void SELECT_B_PROTOCOL_REQ(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cword B1protocol,
					 _cword B2protocol,
                                         _cword B3protocol,
                                         _cstruct B1configuration,
                                         _cstruct B2configuration,
                                         _cstruct B3configuration);
	void CONNECT_RESP(_cword ApplId, _cword Messagenumber,
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
                                         _cstruct Facilitydataarray);

	void CONNECT_ACTIVE_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

	void CONNECT_B3_ACTIVE_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

	void CONNECT_B3_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cword Reject,
					 _cstruct NCPI);

	void CONNECT_B3_T90_ACTIVE_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

	void DATA_B3_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cword DataHandle);

	void DISCONNECT_B3_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

	void DISCONNECT_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

	void FACILITY_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cword FacilitySelector);

	void INFO_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

	void MANUFACTURER_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr,
					 _cdword ManuID,
					 _cdword Class,
                                         _cdword Function,
                                         _cstruct ManuData);

	void RESET_B3_RESP(_cword ApplId, _cword Messagenumber,
					 _cdword adr);

};

#endif

