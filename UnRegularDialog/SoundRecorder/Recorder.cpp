// Recorder.cpp : implementation file
//

#include "stdafx.h"
#include "SoundRecorder.h"
#include "Recorder.h"
#include "afxdialogex.h"


// CRecorder dialog

IMPLEMENT_DYNAMIC(CRecorder, CDialogEx)

CRecorder::CRecorder(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecorder::IDD, pParent)
{
	m_isRecording = false;
}

CRecorder::~CRecorder()
{
}

void CRecorder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecorder, CDialogEx)
	ON_MESSAGE(MM_WIM_DATA,&CRecorder::MM_WIM_DATA_FUNC)
END_MESSAGE_MAP()


// CRecorder message handlers
void CRecorder::StartRecord(CString storeFileName,WAVEFORMATEX* pFormat)
{
	m_isRecording = true;

	m_FileName = storeFileName;

	if (pFormat == NULL)
	{
		m_Format.wFormatTag = 1;
		m_Format.nChannels = 1;
		m_Format.nSamplesPerSec = 16000;
		m_Format.nAvgBytesPerSec = 32000;
		m_Format.nBlockAlign = 2;
		m_Format.wBitsPerSample = 16;
		m_Format.cbSize = 0;
	}
	else
	{
		m_Format = *pFormat;
	}

	MMRESULT ret;

	ret = waveInOpen(&m_hRecord,WAVE_MAPPER,&m_Format,(DWORD)m_hWnd,NULL,CALLBACK_WINDOW);
	if (ret != MMSYSERR_NOERROR)
	{
		MessageBox(L"error1");

		m_isRecording = false;

		return;
	}

	for (int i = 0; i < 3; i++)
	{
		AddBufferQueue();
	}

	ret = waveInStart(m_hRecord);
	if (ret != MMSYSERR_NOERROR)
	{
		MessageBox(L"error4");

		m_isRecording = false;

		return;
	}

	m_hFile = NULL;

	CreateWaveFile();
}

void CRecorder::StopRecord()
{
	waveInReset(m_hRecord);
	waveInClose(m_hRecord);
	CloseSoundFile();
}

bool CRecorder::IsRecording()
{
	return m_isRecording;
}

int CRecorder::GetVolume()
{
	int nVal;
	nVal = (abs(m_volume))/100;
	if (nVal >= 100)
	{
		nVal = 100;
	}

	return nVal;
}

void CRecorder::AddBufferQueue()
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

LRESULT CRecorder::MM_WIM_DATA_FUNC(UINT , LONG parm2)
{
	TRACE0("wave in xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

	TRACE0("wavein\n");

	MMRESULT mmReturn = 0;

	LPWAVEHDR pHdr = (LPWAVEHDR) parm2;



	m_volume = *(short *) pHdr->lpData;

	int volumex = m_volume;

	if (volumex < 0)
	{
		volumex = -volumex;
	}

	TRACE1("volumex:%d\n",volumex*100 * 2/32767);

	m_volume *= 0.6;

	int nVal;
	nVal = (abs(m_volume))/100;
	if (nVal >= 100)
	{
		nVal = 100;
	}

	WriteSoundFile((LPSTR)pHdr->lpData);

	TRACE1("volume:%d\n",nVal);

	TRACE1("bytes recorded:%d\n",pHdr->dwBytesRecorded);
	TRACE1("buffer length:%d\n",pHdr->dwBufferLength);

	mmReturn = ::waveInUnprepareHeader(m_hRecord, pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
		return 0;
	}

	mmReturn = ::waveInPrepareHeader(m_hRecord,pHdr, sizeof(WAVEHDR));
	if(mmReturn)
	{
		return 0;
	}
	else 
	{
		mmReturn = ::waveInAddBuffer(m_hRecord, pHdr, sizeof(WAVEHDR));
		if(mmReturn)
		{
		}
		else
		{
			return 0;
		}
	}

	delete pHdr->lpData;
	delete pHdr;

	return S_OK;
}

bool CRecorder::CreateWaveFile()
{
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

bool CRecorder::WriteSoundFile(LPSTR ptr)
{
	//write data in buffer to file
	int length = mmioWrite(m_hFile,ptr,m_Format.nBlockAlign * 1000);
	if(length == m_Format.nBlockAlign * 1000)
		return true;

	return false;
}

void CRecorder::CloseSoundFile()
{
	if(m_hFile)
	{
		::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
		::mmioAscend(m_hFile, &m_MMCKInfoParent, 0);

		::mmioClose(m_hFile, 0);
		m_hFile = NULL;
	}	
}
