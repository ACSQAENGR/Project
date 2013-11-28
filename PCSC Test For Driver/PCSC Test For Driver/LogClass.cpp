// LogClass.cpp : implementation file
//

#include "stdafx.h"
#include "LogClass.h"

// CLogClass

IMPLEMENT_DYNAMIC(CLogClass, CWnd)

CLogClass::CLogClass()
{

}

CLogClass::~CLogClass()
{
}


BEGIN_MESSAGE_MAP(CLogClass, CWnd)
END_MESSAGE_MAP()



// CLogClass message handlers
void CLogClass::AddToLogs(CEdit *txtbox, CString msg)
{
	CString strOldLogs;
	txtbox->GetWindowText(strOldLogs);
	strOldLogs += msg;
	strOldLogs += "\r\n";
	txtbox->SetWindowText(strOldLogs);

	int loglen = txtbox->GetWindowTextLengthA();
	txtbox->SetSel(loglen,loglen);
}



CString AddSpace(int numspace)
{
	CString sp, strOut;
	sp = "-";
	strOut = "";
	for(int i = 0; i < numspace; i++)
	{
		strOut += sp;
	}
	strOut += " ";
	return strOut;
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg)
{
	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg, CString msg2)
{

	msg += "\t";
	msg += msg2;

	CString msg3;
	msg3 = "";
	msg3 = AddSpace(numIndent);
	msg3+=msg;
	AddToLogs(txtbox,msg3);
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg, bool bVal)
{
	msg += "\t";
	if(bVal == true) msg+= "TRUE";
	else msg += "FALSE";
	
	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg,int int_value)
{

	char strvalue[50];
	sprintf_s(strvalue,50,"%d",int_value);
	msg += "\t";
	msg += strvalue;
	
	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg, ULONG ulvalue)
{
	char strvalue[50];
	sprintf_s(strvalue,50,"%08X",ulvalue);
	msg += "\t";
	msg += "0x";
	msg += strvalue;

	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);

}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg, unsigned char *utf8char_value, int len)
{

	char *pstr;
	pstr = new char[len + 1];
	memset(pstr,'\0',len + 1);

		memcpy_s(pstr, len + 1, utf8char_value,len);


	if(msg != "")msg += "\t";
	msg += pstr;

	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);

	delete [] pstr;
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg, unsigned char *Hex_value, int len, bool bSpaced)
{
	char *pstr;
	char temp[5];
	memset(temp,'\0',5);
	int chLen = bSpaced ? len*3:len*2;
	char *fmat = bSpaced ? "%02X ": "%02X";
	int fmatlen = bSpaced ? 3 : 2;
	pstr = new char[chLen + 1];
	memset(pstr,'\0',chLen + 1);
	for(int i = 0; i < len; i++)
	{
		sprintf_s(temp,5,fmat,*(Hex_value + i));
		memcpy_s(pstr + i*fmatlen,fmatlen,temp,fmatlen);
	}
	if(msg != "")msg += "\t";
	msg += pstr;

	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);

	delete [] pstr;
}

void CLogClass::AddToLogs(int numIndent, CEdit *txtbox, CString msg, unsigned char *Hex_value, ULONG ulLen, bool bSpaced)
{
	char*  pstr;
	char temp[5];
	
	memset(temp,'\0',5);
	int chLen = bSpaced ? ulLen*3 + 1:ulLen*2 + 1;
	pstr = new char[chLen + 1];
	memset(pstr,'\0',chLen + 1);

		char* fmat = bSpaced ? "%02X ": "%02X";
		int fmatlen = bSpaced ? 3 : 2;

		for(int i = 0; i < ulLen; i++)
		{
			sprintf_s(temp,5,fmat,*(Hex_value + i));
			memcpy_s(pstr + i*fmatlen,fmatlen,temp,fmatlen);
		}

	
	if(msg != "")msg += "\t";
	msg += pstr;

	
	CString msg2;
	msg2 = "";
	msg2 = AddSpace(numIndent);
	msg2+=msg;
	AddToLogs(txtbox,msg2);

	delete [] pstr;

}

//listbox
int CLogClass::AddToList(CListBox *listbox, CString msg)
{
	int i = listbox->AddString(msg);
	listbox->SetCurSel(i);
	return i;
}

void CLogClass::AddToList(CListBox *listbox, CString msg,int int_value)
{
	char strvalue[50];
	sprintf_s(strvalue,50,"%d",int_value);
	msg += " ";
	msg += strvalue;
	AddToList(listbox,msg);
}

void CLogClass::AddToList(CListBox *listbox, CString msg, ULONG ulvalue)
{
	char strvalue[50];
	sprintf_s(strvalue,50,"0x%08X",ulvalue);
	msg += " ";
	msg += strvalue;
	AddToList(listbox,msg);
}

int CLogClass::AddToList(CListBox *listbox, CString msg,int int_value, CString TailMsg)
{
	char strvalue[50];
	sprintf_s(strvalue,50,"%d",int_value);
	msg += " ";
	msg += strvalue;
	msg += " ";
	msg += TailMsg;
	return AddToList(listbox,msg);

}

int CLogClass::AddToList(CListBox *listbox, CString msg,ULONG ulvalue, CString TailMsg)
{
	char strvalue[50];
	sprintf_s(strvalue,50,"%X",ulvalue);
	msg += " ";
	msg += strvalue;
	msg += " ";
	msg += TailMsg;
	return AddToList(listbox,msg);

}

int CLogClass::AddToList(CListBox *listbox, CString msg,ULONG ulvalue, CString msg2, ULONG ulvalue2)
{
	char strvalue[50];
	sprintf_s(strvalue,50,"%X",ulvalue);
	msg += " ";
	msg += strvalue;
	msg += " ";
	msg += msg2;
	msg += " ";
	sprintf_s(strvalue,50,"%X",ulvalue2);
	msg += strvalue;
	return AddToList(listbox,msg);

}

int CLogClass::AddToList(CListBox *listbox, CString msg, unsigned char *utf8char_value, int len)
{
	char *pstr;

		
	pstr = new char[len + 1];
	memset(pstr,'\0',len +1);
	memcpy_s(pstr,len+1,utf8char_value,len);

	msg += " ";
	msg += pstr;
	
	delete [] pstr;
	return AddToList(listbox,msg);
}

