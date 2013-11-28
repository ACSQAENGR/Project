// PCSCClass.cpp : implementation file
//

#include "stdafx.h"
#include "PCSC Test For Driver.h"
#include "PCSCClass.h"


// CPCSCClass

IMPLEMENT_DYNAMIC(CPCSCClass, CWnd)

CPCSCClass::CPCSCClass(CEdit* m_logs)
{
	m_logobj = m_logs;
	m_cbListObj = NULL;
}

CPCSCClass::~CPCSCClass()
{
}


BEGIN_MESSAGE_MAP(CPCSCClass, CWnd)
END_MESSAGE_MAP()



// CPCSCClass message handlers

CString CPCSCClass::TranslatePCSCError(){
	CString xtr = "";
	char buff[100];
	memset(buff,0,100);
	switch(RetCode){
		case SCARD_F_INTERNAL_ERROR:
			return "An internal consistency check failed";
		case SCARD_E_CANCELLED:
			return "The action was cancelled by an SCardCancel request";
			
		case SCARD_E_INVALID_HANDLE:
			return "The supplied handle was invalid";
			
		case SCARD_E_INVALID_PARAMETER:
			return "One or more of the supplied parameters could not be properly interpreted";
			
		case SCARD_E_INVALID_TARGET:
			return "Registry startup information is missing or invalid";
			
		case SCARD_E_NO_MEMORY:
			return "Not enough memory available to complete this command";
			
		case SCARD_F_WAITED_TOO_LONG:
			return "An internal consistency timer has expired";
			
		case SCARD_E_INSUFFICIENT_BUFFER:
			return "The data buffer to receive returned data is too small for the returned data";
			
		case SCARD_E_UNKNOWN_READER:
			return "The specified reader name is not recognized";
			
		case SCARD_E_TIMEOUT:
			return "The user-specified timeout value has expired";
			
		case SCARD_E_SHARING_VIOLATION:
			return "The smart card cannot be accessed because of other connections outstanding";
			
		case SCARD_E_NO_SMARTCARD:
			return "The operation requires a Smart Card, but no Smart Card is currently in the device";
			
		case SCARD_E_UNKNOWN_CARD:
			return "The specified smart card name is not recognized";
			
		case SCARD_E_CANT_DISPOSE:
			return "The system could not dispose of the media in the requested manner";
			
		case SCARD_E_PROTO_MISMATCH:
			return "The requested protocols are incompatible with the protocol currently in use with the smart card";
			
		case SCARD_E_NOT_READY:
			return "The reader or smart card is not ready to accept commands";
			
		case SCARD_E_INVALID_VALUE:
			return "One or more of the supplied parameters values could not be properly interpreted";
			
		case SCARD_E_SYSTEM_CANCELLED:
			return "The action was cancelled by the system, presumably to log off or shut down";
			
		case SCARD_F_COMM_ERROR:
			return "An internal communications error has been detected";
			
		case SCARD_F_UNKNOWN_ERROR:
			return "An internal error has been detected, but the source is unknown";
			
		case SCARD_E_INVALID_ATR:
			return "An ATR obtained from the registry is not a valid ATR string";
			
		case SCARD_E_NOT_TRANSACTED:
			return "An attempt was made to end a non-existent transaction";
			
		case SCARD_E_READER_UNAVAILABLE:
			return "The specified reader is not currently available for use";
			
		case SCARD_P_SHUTDOWN:
			return "PRIVATE -- Internal flag to force server termination";
			
		case SCARD_E_PCI_TOO_SMALL:
			return "The PCI Receive buffer was too small";
			
		case SCARD_E_READER_UNSUPPORTED:
			return "The reader driver does not meet minimal requirements for support";
			
		case SCARD_E_DUPLICATE_READER:
			return "The reader driver did not produce a unique reader name";
			
		case SCARD_E_CARD_UNSUPPORTED:
			return "The smart card does not meet minimal requirements for support";
			
		case SCARD_E_NO_SERVICE:
			return "The Smart card resource manager is not running";
			
		case SCARD_E_SERVICE_STOPPED:
			return "The Smart card resource manager has shut down";
			
		case SCARD_W_UNSUPPORTED_CARD:
			return "The reader cannot communicate with the smart card, due to ATR configuration conflicts";
			
		case SCARD_W_UNRESPONSIVE_CARD:
			return "The smart card is not responding to a reset";
			
		case SCARD_W_UNPOWERED_CARD:
			return "Power has been removed from the smart card, so that further communication is not possible";
			
		case SCARD_W_RESET_CARD:
			return "The smart card has been reset, so any shared state information is invalid";
			
		case SCARD_W_REMOVED_CARD:
			return "The smart card has been removed, so that further communication is not possible";
			
		default :
			
			sprintf_s(buff,100, "Undefined Error!\n ErrorCode: %X", RetCode);
			xtr = buff;
			return xtr;
	}

}


bool CPCSCClass::EstablishContext()
{
	RetCode = SCardEstablishContext(
	SCARD_SCOPE_USER,
	NULL,
	NULL,
	&hContext);

	if(RetCode == SCARD_S_SUCCESS)
	{
		mylog.AddToLogs(m_logobj,"SCardEstablishContext Success!");
		return true;
	}
	else
	{
		mylog.AddToLogs(m_logobj,"error: SCardEstablishContext Failed!");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		hContext = 0;
		return false;
	}
}

bool CPCSCClass::ListReadernames(CComboBox* m_cblist)
{
	char *pReaderList = NULL;
	DWORD ReaderListSize = SCARD_AUTOALLOCATE;
	char *pch;

	if(m_cblist == NULL)
	{
		mylog.AddToLogs(m_logobj,"error: NULL combobox class");
		return false;
	}
	
	//save the combobox to class
	m_cbListObj = m_cblist;

	m_cblist->ResetContent();

	RetCode = SCardListReadersA(
		hContext,
		NULL,
		(LPSTR)&pReaderList,
		&ReaderListSize);

	if (RetCode != SCARD_S_SUCCESS)
	{
		mylog.AddToLogs(m_logobj,"error: SCardListReaders Failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;

	}
	else
	{
		mylog.AddToLogs(m_logobj,"SCardListReaders Success");
		
	}

	pch = pReaderList;

	while (*pch != 0)
	{
		m_cblist->AddString (pch);
		pch += strlen (pch) + 1;
	}
	m_cblist->SetCurSel(0);


	RetCode = SCardFreeMemory( hContext, pReaderList );
	if (RetCode != SCARD_S_SUCCESS)
	{
		mylog.AddToLogs(m_logobj,"error: SCardFreeMemory Failed");
	}

	return true;
}

bool CPCSCClass::Connect()
{
	char ReaderName[100];
	int ReaderSelected = 0;

	if(m_cbListObj == NULL)
	{
		mylog.AddToLogs(m_logobj,"error: List readers first");
		return false;
	}
	ReaderSelected = m_cbListObj->GetCurSel();
	m_cbListObj->GetLBText (ReaderSelected, ReaderName);

	Protocol = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;

	RetCode = SCardConnectA(
		hContext,
		ReaderName,
		SCARD_SHARE_EXCLUSIVE,
		Protocol,
        &hCard,
		&Protocol);

	
	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardConnectA failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	IO_REQ.dwProtocol = Protocol;
	IO_REQ.cbPciLength = sizeof(SCARD_IO_REQUEST);

	mylog.AddToLogs(m_logobj,"SCardConnectA Success");
	return true;
}

bool CPCSCClass::BeginTransaction()
{
	RetCode = SCardBeginTransaction(hCard);

	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardBeginTransaction failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	mylog.AddToLogs(m_logobj,"SCardBeginTransaction Success");
	return true;
}

bool CPCSCClass::Transmit(CString cstrApdu)
{
	unsigned char sendbuff[270];
	unsigned char recvbuff[270];
	int apdulen = 0;
	DWORD recvlen = 2;
	CConvertData cvrtObj;
	memset(sendbuff,0,270);
	memset(recvbuff,0,270);

	cvrtObj.HexStringToByteArray(cstrApdu,NULL,&apdulen);
	cvrtObj.HexStringToByteArray(cstrApdu,sendbuff,&apdulen);
	
	mylog.AddToLogs(0,m_logobj,"send:",sendbuff,apdulen,true);

	if(apdulen < 5)
	{
		mylog.AddToLogs(m_logobj,"error: command too short");
	}

	if(apdulen == 5) recvlen = 2 + sendbuff[4];

	RetCode = SCardTransmit(
					hCard,
					&IO_REQ,
					sendbuff,
					apdulen,
					NULL,  //   IN OUT LPSCARD_IO_REQUEST pioRecvPci,
					recvbuff,
					&recvlen);
	
	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardTransmit failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	mylog.AddToLogs(m_logobj,"SCardTransmit Success");

	mylog.AddToLogs(0,m_logobj,"recv:",recvbuff,recvlen,true);

	return true;
}

bool CPCSCClass::EndTransaction(DWORD EndDisposition)
{
	
	RetCode = SCardEndTransaction(hCard,EndDisposition);
	
	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardEndTransaction failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	mylog.AddToLogs(m_logobj,"SCardEndTransaction Success");
	return true;
}

bool CPCSCClass::Disconnect(DWORD EndDisposition)
{
	RetCode = SCardDisconnect(hCard,EndDisposition);
	
	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardDisconnect failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	mylog.AddToLogs(m_logobj,"SCardDisconnect Success");
	return true;
}


bool CPCSCClass::ReleaseContext()
{
	RetCode = SCardReleaseContext(hContext);
	
	if (RetCode != SCARD_S_SUCCESS)
	{	
		mylog.AddToLogs(m_logobj,"error: SCardReleaseContext failed");
		mylog.AddToLogs(m_logobj,TranslatePCSCError());
		return false;
	}
	
	mylog.AddToLogs(m_logobj,"SCardReleaseContext Success");
	return true;
}

