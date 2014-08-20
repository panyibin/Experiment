
// SoundRecorderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoundRecorder.h"
#include "SoundRecorderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

short val;
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


// CSoundRecorderDlg dialog




CSoundRecorderDlg::CSoundRecorderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoundRecorderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoundRecorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSoundRecorderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSoundRecorderDlg::OnBnClickedStartRecord)
	ON_BN_CLICKED(IDC_BUTTON2, &CSoundRecorderDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON3, &CSoundRecorderDlg::OnBnClickedSetting)
	ON_BN_CLICKED(IDC_BUTTON4, &CSoundRecorderDlg::OnBnClickedCheckDevice)
	ON_MESSAGE(MM_WIM_DATA,&CSoundRecorderDlg::MM_WIM_DATA_FUNC)
END_MESSAGE_MAP()


// CSoundRecorderDlg message handlers

BOOL CSoundRecorderDlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	m_recorder = new CRecorder;
	m_recorder->Create(IDD_RECORDER);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoundRecorderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSoundRecorderDlg::OnPaint()
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
HCURSOR CSoundRecorderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSoundRecorderDlg::OnBnClickedStartRecord()
{
	//MMRESULT ret;

	//m_Format.wFormatTag = 1;
	//m_Format.nChannels = 1;
	//m_Format.nSamplesPerSec = 16000;//22050;
	//m_Format.nAvgBytesPerSec = 32000;//44100;
	//m_Format.nBlockAlign = 2;
	//m_Format.wBitsPerSample = 16;
	//m_Format.cbSize = 0;

	//ret = waveInOpen(&m_hRecord,WAVE_MAPPER,&m_Format,(DWORD)m_hWnd,NULL,CALLBACK_WINDOW);
	//if (ret != MMSYSERR_NOERROR)
	//{
	//	MessageBox(L"error1");
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	AddBufferQueue();
	//}

	//ret = waveInStart(m_hRecord);
	//if (ret != MMSYSERR_NOERROR)
	//{
	//	MessageBox(L"error4");
	//}

	//m_hFile = NULL;
	//CreateWaveFile();

	m_recorder->StartRecord(L"test2.wav");
}

void CSoundRecorderDlg::AddBufferQueue()
{
	MMRESULT ret;

	LPWAVEHDR pHdr = new WAVEHDR;

	ZeroMemory(pHdr, sizeof(WAVEHDR));

	pHdr->lpData = (LPSTR)new BYTE[m_Format.nBlockAlign * 1000];
	pHdr->dwBufferLength = m_Format.nBlockAlign * 1000;

	ret = waveInPrepareHeader(m_hRecord,pHdr,sizeof(WAVEHDR));
	if (ret != MMSYSERR_NOERROR)
	{
		MessageBox(L"error2");
	}

	ret = waveInAddBuffer(m_hRecord,pHdr,sizeof(WAVEHDR));
	if (ret != MMSYSERR_NOERROR)
	{
		MessageBox(L"error3");
	}
}

LRESULT CSoundRecorderDlg::MM_WIM_DATA_FUNC(UINT , LONG parm2)
{
	TRACE0("wave in xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

	TRACE0("wavein\n");

	MMRESULT mmReturn = 0;

	LPWAVEHDR pHdr = (LPWAVEHDR) parm2;

	val = *(short *) pHdr->lpData;
	val *= 0.6;

	int nVal;
	nVal = (abs(val))/100;
	if (nVal >= 100)
	{
		nVal = 100;
	}

	Write((LPSTR)pHdr->lpData);

	TRACE1("volume:%d\n",nVal);

	mmReturn = ::waveInUnprepareHeader(m_hRecord, pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
		return 0;
	}

	mmReturn = ::waveInPrepareHeader(m_hRecord,pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
	}
	else 
	{
		mmReturn = ::waveInAddBuffer(m_hRecord, pHdr, sizeof(WAVEHDR));
		if(mmReturn);
		else return 0;  
	}

	delete pHdr->lpData;
	delete pHdr;

	return S_OK;
}


void CSoundRecorderDlg::OnBnClickedStop()
{
	/*waveInReset(m_hRecord);
	waveInClose(m_hRecord);
	Close();*/
	m_recorder->StopRecord();
}


void CSoundRecorderDlg::OnBnClickedSetting()
{
	WinExec("control.exe mmsys.cpl,,recording",SW_NORMAL);
}


void CSoundRecorderDlg::OnBnClickedCheckDevice()
{

}

bool CSoundRecorderDlg::CreateWaveFile()
{
	m_FileName = L"test.wav";
	if(m_hFile) 
		return FALSE;	
	
	m_hFile = ::mmioOpen(m_FileName.GetBuffer(0),NULL, MMIO_CREATE|MMIO_WRITE|MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
	if(m_hFile == NULL) 
	{
		return FALSE;
	}
	// create RIFF segment
	ZeroMemory(&m_MMCKInfoParent, sizeof(MMCKINFO));
	m_MMCKInfoParent.fccType = mmioFOURCC('W','A','V','E');
	MMRESULT mmResult = ::mmioCreateChunk( m_hFile,&m_MMCKInfoParent, MMIO_CREATERIFF);
	//create format segment
	ZeroMemory(&m_MMCKInfoChild, sizeof(MMCKINFO));
	m_MMCKInfoChild.ckid = mmioFOURCC('f','m','t',' ');
	m_MMCKInfoChild.cksize = sizeof(WAVEFORMATEX) + m_Format.cbSize;
	mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
	mmResult = ::mmioWrite(m_hFile, (char*)&m_Format, sizeof(WAVEFORMATEX) + m_Format.cbSize); 
	mmResult = ::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
	//create date segment
	m_MMCKInfoChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
	return TRUE;
}

bool CSoundRecorderDlg::Write(LPSTR ptr)
{
//write data in buffer to file
		int length = mmioWrite(m_hFile,ptr,m_Format.nBlockAlign * 1000);
		if(length == m_Format.nBlockAlign * 1000)
			return true;
	
		return false;
}

void CSoundRecorderDlg::Close()
{
	if(m_hFile)
	{
		::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
		::mmioAscend(m_hFile, &m_MMCKInfoParent, 0);

		::mmioClose(m_hFile, 0);
		m_hFile = NULL;
	}	

}