// PCSC Test For DriverDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "PCSCClass.h"

// CPCSCTestForDriverDlg dialog
class CPCSCTestForDriverDlg : public CDialog
{
// Construction
public:
	CPCSCTestForDriverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PCSCTESTFORDRIVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_chk1;
	CButton m_chk2;
	CButton m_chk3;
	CButton m_chk4;
	CButton m_chk5;
	// yeah
	CButton m_chk6;
	CButton m_chk7;
	CButton m_chk8;
	CEdit m_txt_log;
	CEdit m_txt_apdu;
	CComboBox m_cb_readerlist;
	afx_msg void OnBnClickedBtnEstblishContext();
	afx_msg void OnBnClickedBtnListreaders();

	CPCSCClass *pcscObj;


	
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnBeginTransaction();
	afx_msg void OnBnClickedBtnEndTransaction();
	CComboBox m_cb_end_disposition;
	afx_msg void OnBnClickedBtnDisconnect();
	afx_msg void OnBnClickedBtnReleaseContext();
	afx_msg void OnBnClickedBtnOneclick();
	afx_msg void OnBnClickedBtnTransmit();
};
