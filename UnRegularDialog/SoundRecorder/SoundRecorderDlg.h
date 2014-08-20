
// SoundRecorderDlg.h : header file
//

#pragma once

#include <MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#include "Recorder.h"


// CSoundRecorderDlg dialog
class CSoundRecorderDlg : public CDialogEx
{
// Construction
public:
	CSoundRecorderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SOUNDRECORDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HWAVEIN m_hRecord;
	WAVEFORMATEX m_Format;
	DWORD m_threadID;
	HMMIO m_hFile;
	CString m_FileName;
	MMCKINFO m_MMCKInfoParent;
	MMCKINFO m_MMCKInfoChild;

	afx_msg LRESULT MM_WIM_DATA_FUNC(UINT /*parm1*/, LONG parm2);

	afx_msg void OnBnClickedStartRecord();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedSetting();
	afx_msg void OnBnClickedCheckDevice();

	void AddBufferQueue();

	bool CreateWaveFile();
	void Close();
	bool Write(LPSTR ptr);

	CRecorder* m_recorder;
};
