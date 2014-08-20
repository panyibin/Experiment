
// CDHtmlCrashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDHtmlCrash.h"
#include "CDHtmlCrashDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCDHtmlCrashDlg dialog




CCDHtmlCrashDlg::CCDHtmlCrashDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCDHtmlCrashDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDHtmlCrashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCDHtmlCrashDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCDHtmlCrashDlg::OnBnClickedGotoSite1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCDHtmlCrashDlg::OnBnClickedGotoSite2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCDHtmlCrashDlg::OnBnClickedGotoSite3)
END_MESSAGE_MAP()


// CCDHtmlCrashDlg message handlers

BOOL CCDHtmlCrashDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	m_pCDhtmlTest = new CDHtmlTest;

	m_pCDhtmlTest->Create(IDD_DHTMLTEST);

	m_pCDhtmlTest->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCDHtmlCrashDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCDHtmlCrashDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCDHtmlCrashDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCDHtmlCrashDlg::OnBnClickedGotoSite1()
{
	// TODO: Add your control notification handler code here
	m_pCDhtmlTest->Navigate(L"http://www.baidu.com");
	
	m_pCDhtmlTest->Navigate(L"http://www.google.com");

	m_pCDhtmlTest->Navigate(L"http://www.baidu.com");

	m_pCDhtmlTest->Navigate(L"http://www.google.com");

	m_pCDhtmlTest->Navigate(L"http://www.baidu.com");

	m_pCDhtmlTest->Navigate(L"http://www.google.com");

}


void CCDHtmlCrashDlg::OnBnClickedGotoSite2()
{
	// TODO: Add your control notification handler code here
	m_pCDhtmlTest->Navigate(L"D:\\test\\VoiceSearch\\speaking.html");
	
	Sleep(100);
	
	m_pCDhtmlTest->Navigate(L"D:\\test\\VoiceSearch\\speakingFinish.html");

	Sleep(100);

	m_pCDhtmlTest->Navigate(L"D:\\test\\VoiceSearch\\recognizing.html");
}


void CCDHtmlCrashDlg::OnBnClickedGotoSite3()
{
	// TODO: Add your control notification handler code here
	m_pCDhtmlTest->Navigate(L"http://www.bing.com");
}
