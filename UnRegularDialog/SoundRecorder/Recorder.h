#pragma once

#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

// CRecorder dialog

class CRecorder : public CDialogEx
{
	DECLARE_DYNAMIC(CRecorder)

public:
	CRecorder(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecorder();

// Dialog Data
	enum { IDD = IDD_RECORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	HWAVEIN m_hRecord;
	WAVEFORMATEX m_Format;
	DWORD m_threadID;
	HMMIO m_hFile;
	CString m_FileName;
	MMCKINFO m_MMCKInfoParent;
	MMCKINFO m_MMCKInfoChild;

	int m_volume;
	bool m_isRecording;

private:
	void AddBufferQueue();
	bool CreateWaveFile();
	void CloseSoundFile();
	bool WriteSoundFile(LPSTR ptr);
	afx_msg LRESULT MM_WIM_DATA_FUNC(UINT, LONG parm2);

public:
	void StartRecord(CString storeFileName,WAVEFORMATEX* pFormat = NULL);
	void StopRecord();
	bool IsRecording();
	int GetVolume();
};
