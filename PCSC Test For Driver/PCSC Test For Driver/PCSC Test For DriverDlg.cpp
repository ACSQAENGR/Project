// PCSC Test For DriverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCSC Test For Driver.h"
#include "PCSC Test For DriverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPCSCTestForDriverDlg dialog



CPCSCTestForDriverDlg::CPCSCTestForDriverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPCSCTestForDriverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CPCSCTestForDriverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_CHECK2, m_chk2);
	DDX_Control(pDX, IDC_CHECK3, m_chk3);
	DDX_Control(pDX, IDC_CHECK4, m_chk4);
	DDX_Control(pDX, IDC_CHECK5, m_chk5);
	DDX_Control(pDX, IDC_CHECK6, m_chk6);
	DDX_Control(pDX, IDC_CHECK7, m_chk7);
	DDX_Control(pDX, IDC_CHECK8, m_chk8);
	DDX_Control(pDX, IDC_TXT_LOG, m_txt_log);
	DDX_Control(pDX, IDC_TXT_APDU, m_txt_apdu);
	DDX_Control(pDX, IDC_CB_READERLIST, m_cb_readerlist);
	DDX_Control(pDX, IDC_CB_END_DISPOSITION, m_cb_end_disposition);
}

BEGIN_MESSAGE_MAP(CPCSCTestForDriverDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ESTBLISH_CONTEXT, &CPCSCTestForDriverDlg::OnBnClickedBtnEstblishContext)
	ON_BN_CLICKED(IDC_BTN_LISTREADERS, &CPCSCTestForDriverDlg::OnBnClickedBtnListreaders)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CPCSCTestForDriverDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_BEGIN_TRANSACTION, &CPCSCTestForDriverDlg::OnBnClickedBtnBeginTransaction)
	ON_BN_CLICKED(IDC_BTN_END_TRANSACTION, &CPCSCTestForDriverDlg::OnBnClickedBtnEndTransaction)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CPCSCTestForDriverDlg::OnBnClickedBtnDisconnect)
	ON_BN_CLICKED(IDC_BTN_RELEASE_CONTEXT, &CPCSCTestForDriverDlg::OnBnClickedBtnReleaseContext)
	ON_BN_CLICKED(IDC_BTN_ONECLICK, &CPCSCTestForDriverDlg::OnBnClickedBtnOneclick)
	ON_BN_CLICKED(IDC_BTN_TRANSMIT, &CPCSCTestForDriverDlg::OnBnClickedBtnTransmit)
END_MESSAGE_MAP()


// CPCSCTestForDriverDlg message handlers

BOOL CPCSCTestForDriverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	pcscObj = new CPCSCClass(&m_txt_log);
	m_cb_end_disposition.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPCSCTestForDriverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPCSCTestForDriverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPCSCTestForDriverDlg::OnBnClickedBtnEstblishContext()
{
	if(pcscObj->EstablishContext()) m_chk1.SetCheck(1);
	else m_chk1.SetCheck(0);
}

void CPCSCTestForDriverDlg::OnBnClickedBtnListreaders()
{
	if(pcscObj->ListReadernames(&m_cb_readerlist)) m_chk2.SetCheck(1);
	else m_chk2.SetCheck(0);

}


void CPCSCTestForDriverDlg::OnBnClickedBtnConnect()
{
	if(pcscObj->Connect()) m_chk3.SetCheck(1);
	else m_chk3.SetCheck(0);
}

void CPCSCTestForDriverDlg::OnBnClickedBtnBeginTransaction()
{
	if(pcscObj->BeginTransaction()) m_chk4.SetCheck(1);
	else m_chk4.SetCheck(0);
}

void CPCSCTestForDriverDlg::OnBnClickedBtnTransmit()
{
	CString strApdu;
	m_txt_apdu.GetWindowTextA(strApdu);
	if(pcscObj->Transmit(strApdu)) m_chk5.SetCheck(1);
	else m_chk5.SetCheck(0);
}

void CPCSCTestForDriverDlg::OnBnClickedBtnEndTransaction()
{
	DWORD endDisp;
	switch(m_cb_end_disposition.GetCurSel())
	{
	case 0:
		endDisp = SCARD_LEAVE_CARD;//SCARD_LEAVE_CARD;SCARD_EJECT_CARD;SCARD_RESET_CARD;SCARD_UNPOWER_CARD
		break;
	case 1:
		endDisp = SCARD_EJECT_CARD;
		break;
	case 2:
		endDisp = SCARD_RESET_CARD;
		break;
	case 3:
		endDisp = SCARD_UNPOWER_CARD;
		break;
	default:
		endDisp = SCARD_LEAVE_CARD;
	}

	if(pcscObj->EndTransaction(endDisp)) m_chk6.SetCheck(1);
	else m_chk6.SetCheck(0);
}


void CPCSCTestForDriverDlg::OnBnClickedBtnDisconnect()
{
	DWORD endDisp;
	switch(m_cb_end_disposition.GetCurSel())
	{
	case 0:
		endDisp = SCARD_LEAVE_CARD;//SCARD_LEAVE_CARD;SCARD_EJECT_CARD;SCARD_RESET_CARD;SCARD_UNPOWER_CARD
		break;
	case 1:
		endDisp = SCARD_EJECT_CARD;
		break;
	case 2:
		endDisp = SCARD_RESET_CARD;
		break;
	case 3:
		endDisp = SCARD_UNPOWER_CARD;
		break;
	default:
		endDisp = SCARD_LEAVE_CARD;
	}

	if(pcscObj->Disconnect(endDisp)) m_chk7.SetCheck(1);
	else m_chk7.SetCheck(0);
}

void CPCSCTestForDriverDlg::OnBnClickedBtnReleaseContext()
{
	if(pcscObj->ReleaseContext()) m_chk8.SetCheck(1);
	else m_chk8.SetCheck(0);
}

void CPCSCTestForDriverDlg::OnClose()
{
	delete pcscObj;

	CDialog::OnClose();
}


void CPCSCTestForDriverDlg::OnBnClickedBtnOneclick()
{

	if(pcscObj->Connect()) m_chk3.SetCheck(1);
	else m_chk3.SetCheck(0);

	if(pcscObj->BeginTransaction()) m_chk4.SetCheck(1);
	else m_chk4.SetCheck(0);

	CString strApdu;
	m_txt_apdu.GetWindowTextA(strApdu);
	if(pcscObj->Transmit(strApdu)) m_chk5.SetCheck(1);
	else m_chk5.SetCheck(0);

	DWORD endDisp;
	switch(m_cb_end_disposition.GetCurSel())
	{
	case 0:
		endDisp = SCARD_LEAVE_CARD;//SCARD_LEAVE_CARD;SCARD_EJECT_CARD;SCARD_RESET_CARD;SCARD_UNPOWER_CARD
		break;
	case 1:
		endDisp = SCARD_EJECT_CARD;
		break;
	case 2:
		endDisp = SCARD_RESET_CARD;
		break;
	case 3:
		endDisp = SCARD_UNPOWER_CARD;
		break;
	default:
		endDisp = SCARD_LEAVE_CARD;
	}

	if(pcscObj->EndTransaction(endDisp)) m_chk6.SetCheck(1);
	else m_chk6.SetCheck(0);

	if(pcscObj->Disconnect(endDisp)) m_chk7.SetCheck(1);
	else m_chk7.SetCheck(0);
}


