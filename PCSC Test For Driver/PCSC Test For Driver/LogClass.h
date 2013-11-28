#pragma once


// CLogClass

class CLogClass : public CWnd
{
	DECLARE_DYNAMIC(CLogClass)

public:
	CLogClass();
	virtual ~CLogClass();

protected:
	DECLARE_MESSAGE_MAP()

//functions
public:
	//txtbox
	afx_msg void AddToLogs(CEdit *txtbox, CString msg);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg, CString msg2);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg, bool bVal);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg,int int_value);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg,ULONG ulvalue);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg, unsigned char *utf8char_value, int len);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg, unsigned char *Hex_value, int len, bool bSpaced);
	afx_msg void AddToLogs(int numIndent, CEdit *txtbox, CString msg, unsigned char *Hex_value, ULONG ulLen, bool bSpaced);
	

	//listbox
	afx_msg int AddToList(CListBox *listbox, CString msg);//returns the line index of the item
	afx_msg void AddToList(CListBox *listbox, CString msg, int int_value);
	afx_msg void AddToList(CListBox *listbox, CString msg, ULONG ulvalue);
	afx_msg int AddToList(CListBox *listbox, CString msg, unsigned char *utf8char_value, int len);
	afx_msg int AddToList(CListBox *listbox, CString msg, int int_value, CString TailMsg);
	afx_msg int AddToList(CListBox *listbox, CString msg, ULONG ulvalue, CString TailMsg);
	afx_msg int AddToList(CListBox *listbox, CString msg, ULONG ulvalue, CString msg2, ULONG ulvalue2);
	//use byte
	//afx_msg void AddToList(CListBox *listbox, CString msg, void* ptr, int element_size);

};


