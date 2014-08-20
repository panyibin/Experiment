// SoundPlayer.cpp : implementation file
//

#include "stdafx.h"
#include "MySoundPlayer.h"
#include "SoundPlayer.h"
#include "afxdialogex.h"


// CSoundPlayer dialog
const int bufferSize = 1000;

IMPLEMENT_DYNAMIC(CSoundPlayer, CDialogEx)

CSoundPlayer::CSoundPlayer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoundPlayer::IDD, pParent)
{
	m_bWaveHandleValid = FALSE;
	m_hFile = NULL;
	m_bPlaying = FALSE;
}

CSoundPlayer::~CSoundPlayer()
{
}

void CSoundPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSoundPlayer, CDialogEx)
	ON_MESSAGE(MM_WOM_DONE,OnMM_WOM_DONE)
END_MESSAGE_MAP()


// CSoundPlayer message handlers
BOOL CSoundPlayer::Play(CString file, bool bRepeating)
{
	m_bPlaying = TRUE;

	m_FileName = file;

	m_bRepeating = bRepeating;

	//open wave file

	MMRESULT ret;

	ret = OpenWaveFile(m_FileName);
	if (!ret)
	{
		return FALSE;
	}

	ret = ::waveOutOpen(&m_hPlay,WAVE_MAPPER,&m_Format,(DWORD)m_hWnd,NULL,CALLBACK_WINDOW);
	
	if (ret != MMSYSERR_NOERROR)
	{
		m_bPlaying = FALSE;

		return FALSE;
	}

	m_bWaveHandleValid = TRUE;

	//use three buffers to play
	const int bufferNum = 3;
	

	for (int i = 0; i < bufferNum; i++)
	{
		Buffer buf;
		buf.pBuf = new char[m_Format.nBlockAlign * bufferSize];

		ZeroMemory(buf.pBuf,m_Format.nBlockAlign * bufferSize);

		//read sound data into buffer
		ReadWaveDataToBuffer(&buf);

		//begin playing
		if (buf.size > 0)
		{
			AddBufferToQueue(&buf);
		}
		else
		{
			break;
		}
	}

	return TRUE;
}

BOOL CSoundPlayer::ReadWaveDataToBuffer(Buffer *buf)
{
	if (buf == NULL)
	{
		return FALSE;
	}

	buf->size = mmioRead(m_hFile,buf->pBuf,m_Format.nBlockAlign * bufferSize);
	if(buf->size > 0)
	{
		return TRUE;
	}
	else
	{
		if (m_bRepeating)
		{
			mmioSeek(m_hFile,0,SEEK_SET);
			buf->size = mmioRead(m_hFile,buf->pBuf,m_Format.nBlockAlign * bufferSize);
			if (buf->size > 0)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}

		return FALSE;
	}
}

void CSoundPlayer::AddBufferToQueue(Buffer *buf)
{
	if (buf == NULL)
	{
		return;
	}

	MMRESULT mmReturn = 0;

	LPWAVEHDR pHdr = new WAVEHDR;
	if (pHdr == NULL)
	{
		return;
	}

	pHdr->lpData = buf->pBuf;
	pHdr->dwBufferLength = buf->size;
	pHdr->dwFlags = 0;

	mmReturn = waveOutPrepareHeader(m_hPlay,pHdr,sizeof(WAVEHDR));
	if (mmReturn)
	{
		return;
	}

	mmReturn = ::waveOutWrite(m_hPlay,pHdr,sizeof(WAVEHDR));
	if (mmReturn)
	{
		return;
	}
}

LRESULT CSoundPlayer::OnMM_WOM_DONE(UINT parm1, LONG parm2)
{
	TRACE0(".................MM_WOM_DONE.................................\n");
	MMRESULT mmReturn = 0;
	LPWAVEHDR pHdr = (LPWAVEHDR)parm2;
	if (pHdr == NULL)
	{
		return 0;
	}

	mmReturn = ::waveOutUnprepareHeader(m_hPlay,pHdr,sizeof(WAVEHDR));
	if (mmReturn)
	{
		return 0;
	}

	delete pHdr->lpData;
	delete pHdr;

	if(m_bPlaying)
	{
		Buffer buf;
		buf.pBuf = new char[m_Format.nBlockAlign * bufferSize];
		ReadWaveDataToBuffer(&buf);
		if (buf.size > 0)
		{
			AddBufferToQueue(&buf);

			

			return 0;
		}
		else
		{
			Stop();
		}
	}

	return 0;
}

void CSoundPlayer::Stop()
{
	MMRESULT mmReturn = 0;
	if (m_bPlaying && m_bWaveHandleValid == TRUE)
	{
		m_bPlaying = FALSE;
		mmReturn = ::waveOutReset(m_hPlay);
		if (mmReturn)
		{
			return;
		}

		mmReturn = ::waveOutClose(m_hPlay);
		if (mmReturn)
		{
			return;
		}

		m_bWaveHandleValid = FALSE;
	}
}

BOOL CSoundPlayer::OpenWaveFile(CString fileName)
{
	m_hFile = mmioOpen(fileName.GetBuffer(0),NULL,MMIO_READ);
	if (m_hFile == NULL)
	{
		return FALSE;
	}

	m_MMCKInfoParent.fccType = mmioFOURCC('W','A','V','E');
	MMRESULT mmResult = ::mmioDescend(m_hFile,&m_MMCKInfoParent,NULL,MMIO_FINDRIFF);
	if (mmResult)
	{
		return FALSE;
	}

	m_MMCKInfoChild.ckid = mmioFOURCC('f','m','t',' ');
	mmResult = ::mmioDescend(m_hFile,&m_MMCKInfoChild,&m_MMCKInfoParent,MMIO_FINDCHUNK);
	if (mmResult)
	{
		return FALSE;
	}

	DWORD bytesRead = mmioRead(m_hFile,(LPSTR)&m_Format,m_MMCKInfoChild.cksize);
	if (bytesRead < 0)
	{
		return FALSE;
	}

	mmResult = mmioAscend(m_hFile,&m_MMCKInfoChild,0);
	if (mmResult)
	{
		return FALSE;
	}

	m_MMCKInfoChild.ckid = mmioFOURCC('d','a','t','a');
	mmResult = mmioDescend(m_hFile,&m_MMCKInfoChild,&m_MMCKInfoParent,MMIO_FINDCHUNK);
	if (mmResult)
	{
		return FALSE;
	}

	return TRUE;
}
