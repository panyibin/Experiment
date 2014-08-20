#pragma once
#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

// CSoundPlayer dialog
struct Buffer
{
	char* pBuf;
	int size;
};

class CSoundPlayer : public CDialogEx
{
	DECLARE_DYNAMIC(CSoundPlayer)

public:
	CSoundPlayer(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSoundPlayer();

// Dialog Data
	enum { IDD = IDD_SOUNDPLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	HWAVEOUT m_hPlay;
	BOOL m_bPlaying;
	WAVEFORMATEX m_Format;
	CString m_FileName;
	BOOL m_bWaveHandleValid;
	HMMIO m_hFile;
	MMCKINFO m_MMCKInfoParent;
	MMCKINFO m_MMCKInfoChild;
	bool m_bRepeating;

private:
	afx_msg LRESULT OnMM_WOM_DONE(UINT parm1, LONG parm2);
	BOOL OpenWaveFile(CString fileName);
	BOOL ReadWaveDataToBuffer(Buffer *buf);
	void AddBufferToQueue(Buffer *buf);

public:
	BOOL Play(CString file, bool bRepeating = false);
	void Stop();
};


