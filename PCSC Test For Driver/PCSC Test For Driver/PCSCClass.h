#pragma once

#include "LogClass.h"
#include "ConvertData.h"
#include <winscard.h>
// CPCSCClass

class CPCSCClass : public CWnd
{
	DECLARE_DYNAMIC(CPCSCClass)

public:
	CPCSCClass(CEdit* m_logs);
	virtual ~CPCSCClass();
	
	afx_msg bool EstablishContext();
	afx_msg bool ListReadernames(CComboBox* m_cblist);
	afx_msg bool Connect();
	afx_msg bool BeginTransaction();
	afx_msg bool Transmit(CString cstrApdu);
	afx_msg bool EndTransaction(DWORD EndDisposition);
	afx_msg bool Disconnect(DWORD EndDisposition);
	afx_msg bool ReleaseContext();
	
	afx_msg CString TranslatePCSCError();
	
	CEdit* m_logobj;
	CComboBox* m_cbListObj;
	SCARDCONTEXT hContext;
	SCARDHANDLE hCard;
	DWORD Protocol;
	LONG RetCode;
	SCARD_IO_REQUEST IO_REQ;
	char *ReaderName;
	CLogClass mylog;

protected:


	DECLARE_MESSAGE_MAP()

};


