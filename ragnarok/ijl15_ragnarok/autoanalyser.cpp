#include "autoanalyser.hpp"
#include "dllconf.hpp"
#include "peimage.hpp"

extern PEImage* pe;
extern DLLConf* conf;

////////////////////////////////////////////////////////////////////////////////


namespace autoanalyser
{
	template<typename T> inline T getRef(DWORD address);
};


template<typename T> inline T autoanalyser::getRef(DWORD address)
{
	if (::IsBadReadPtr(reinterpret_cast<const void*>(address), sizeof(T)) == 0)
		return *reinterpret_cast<T*>(address);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////


void autoanalyser::addr_aid()
{
	// mov edx, [aid]		; 8B15________
	// mov [ebp-04], ebx	; 895DFC
	// mov [ebp-08], edx	; 8955F8

	BYTE code[] = {
		0x89, 0x5D, 0xFC,	// mov [ebp-04], ebx
		0x89, 0x55, 0xF8,	// mov [ebp-08], edx
	};

	DWORD address = pe->searchCodeRef(code, sizeof(code), -4);
	conf->set_addr(ADDR_AID, address);
	DbgPrint(_T("aid=%08X"), address);
}


void autoanalyser::addr_gamebase()
{
	// push 00000000		; 6A00
	// push 0096FFFF		; 68FFFF9600
	// mov ecx				; 51
	// push 00000001		; 6A01
	// mov ecx, ________	; B9________
	// call ________		; E8________

	// mov ecx, ________	; B9________
	// push 00000000		; 6A00
	// push 0096FFFF		; 68FFFF9600
	// mov edx				; 52
	// push 00000001		; 6A01
	// call ________		; E8________

	BYTE code[] = {
		0x68, 0xFF, 0xFF, 0x96, 0x00,	// push 0096FFFF
	};

	DWORD address = pe->searchCode(code, sizeof(code));
	DWORD addr_shift, addr_gamebase;

	switch (*reinterpret_cast<BYTE*>(address+8))
	{

		case 0xB9:
			addr_shift = address + 14;
			addr_gamebase = address + 9;
			break;

		case 0xE8:
			addr_shift = address + 9;
			addr_gamebase = address - 6;
			break;

		default:
			addr_shift = 0;
			addr_gamebase = 0;
			return;
	}

	DWORD shift = getRef<DWORD>(addr_shift);

	conf->set_addr(ADDR_GAMEBASE, getRef<DWORD>(addr_gamebase));
	DbgPrint(_T("gamebase=%08X"), getRef<DWORD>(addr_gamebase));
	conf->set_addr(ADDR_PUSHTEXT, addr_shift+4+shift);
	DbgPrint(_T("pushtext()=%08X eip=%08X callto=%08X"), addr_shift+4+shift, addr_shift+4, shift);
}


void autoanalyser::addr_actorbase()
{
	// push ebp				; 55
	// mov ebp, esp			; 8BEC
	// mov eax. [ebp+08]	; 8B4508
	// mov ecx, ________	; B9________

	BYTE code[] = {
		0x55,				// push ebp
		0x8B, 0xEC,			// mov ebp, esp
		0x8B, 0x45, 0x08,	// mov eax, [ebp+08]
		0xB9,				// mov ecx
	};

	DWORD address = pe->searchCodeRef(code, sizeof(code), 7);
	conf->set_addr(ADDR_ACTORBASE, address);
	DbgPrint(_T("actorbase=%08X"), address);
}


void autoanalyser::addr_xml_address()
{
	// mov dword ptr [________], ________ ; C705________________

	DWORD addr_string = pe->searchString("192.168.0.100");
	//DWORD addr_string = pe->searchString("211.172.247.110");
	if (addr_string == 0)
		addr_string = pe->searchString("192.168.20.170");

	BYTE code[4];
	*reinterpret_cast<DWORD*>(code) = addr_string;

	DWORD address = pe->searchCodeRef(code, sizeof(code), -4);
	conf->set_addr(ADDR_XML_ADDRESS, address);
	DbgPrint(_T("xml_address=%08X"), address);
}


void autoanalyser::addr_vdtvalue()
{
	// push ________		; 68________
	// push 00000004		; 6A04
	// push 00000000		; 6A00
	// push ________		; 68________	"g_outdoorViewDistance"

	DWORD addr_string = pe->searchString("g_outdoorViewDistance");

	BYTE code[] = {
		0x6A, 0x04,						// push 00000004
		0x6A, 0x00,						// push 00000000
		0x68, 0x00, 0x00, 0x00, 0x00,	// push ________
	};
	*reinterpret_cast<DWORD*>(code+5) = addr_string;

	DWORD address = pe->searchCodeRef(code, sizeof(code), -4);
	conf->set_addr(ADDR_VDT, address-0x1C);
	DbgPrint(_T("vdtvalue=%08X"), address-0x1C);
}


void autoanalyser::addr_netbase()
{
	// push eax			; 50
	// push 000001ED	; 68ED010000
	// call ________	; E8________

	BYTE code[] = {
		0x50,							// push eax
		0x68, 0xED, 0x01, 0x00, 0x00,	// push 000001ED
	};

	DWORD address = pe->searchCode(code, sizeof(code));
	DWORD shift = getRef<DWORD>(address+7);
	DbgPrint(_T("getnetbase()=%08X eip=%08X callto=%08X"), address+11+shift, address+11, shift);

	void* func = reinterpret_cast<void*>(address+11+shift);
	DWORD addr_net;

	__asm
	{
		call [func]
		mov addr_net, eax
	}

	conf->set_addr(ADDR_NETBASE, addr_net);
	DbgPrint(_T("netbase=%08X"), addr_net);
}


void autoanalyser::addr_recvsend()
{
	// mov dword ptr [________], ________	; C705________________

	BYTE code[] = {
		0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,	// jmp 00000000
	};

	DWORD addr_send = pe->searchFF25(_T("ws2_32.dll"), "send");
	*reinterpret_cast<DWORD*>(code+2) = addr_send;
	addr_send = pe->searchCode(code, sizeof(code));

	BYTE code2[4];
	*reinterpret_cast<DWORD*>(code2) = addr_send;
	addr_send = pe->searchCodeRef(code2, sizeof(code2), -4);

	if (addr_send)
	{
		conf->set_addr(ADDR_SEND, addr_send);
		DbgPrint(_T("send=%08X"), addr_send);
	}

	DWORD addr_recv = pe->searchFF25(_T("ws2_32.dll"), "recv");
	*reinterpret_cast<DWORD*>(code+2) = addr_recv;
	addr_recv = pe->searchCode(code, sizeof(code));

	BYTE code3[4];
	*reinterpret_cast<DWORD*>(code3) = addr_recv;
	addr_recv = pe->searchCodeRef(code3, sizeof(code3), -4);

	if (addr_recv)
	{
		conf->set_addr(ADDR_RECV, addr_recv);
		DbgPrint(_T("recv=%08X"), addr_recv);
	}
}


void autoanalyser::addr_charname()
{
	// inc eax				; 40
	// cmp eax, 00000040	; 83F840
	// jb ________			; 72__
	// push edi				; 5F
	// push esi				; 5E
	// push eax ________	; B8________

	BYTE code[] = {
		0x40,				// inc eax
		0x83, 0xF8,	0x40,	// cmp eax, 00000040
		0x72,				// jb
	};

	DWORD address = pe->searchCode(code, sizeof(code));

	if (*reinterpret_cast<BYTE*>(address+8) == 0xB8)
	{
		conf->set_addr(ADDR_CHARNAME, getRef<DWORD>(address+9));
		DbgPrint(_T("charname=%08X"), getRef<DWORD>(address+9));
	}
}


void autoanalyser::addr_cmdjmptable(const BYTE __x)
{
	// cmp edi, 000000A6				; 81FFA6000000
	// ja ________						; 0F87________
	// jmp dword ptr [4*edi+________]	; FF24BD______

	BYTE code[] = {
		0x81, 0xFF, 0x00, 0x00, 0x00, 0x00,	// cmp edi, 000000A6
	};
	code[2] = __x;

	DWORD address = pe->searchCode(code, sizeof(code));

	if (*reinterpret_cast<WORD*>(address+12) == 0x24FF)
	{
		conf->set_addr(ADDR_CMDJMPTBL, getRef<DWORD>(address+15));
		DbgPrint(_T("cmdjmptable=%08X"), getRef<DWORD>(address+15));
	}
}