
// MySoundPlayerDlg.h : header file
//

#pragma once
#include "SoundPlayer.h"


// CMySoundPlayerDlg dialog
class CMySoundPlayerDlg : public CDialogEx
{
// Construction
public:
	CMySoundPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MYSOUNDPLAYER_DIALOG };

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
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop();

	CSoundPlayer* m_soundPlayer;
	CSoundPlayer m_soundPlayer2;
	afx_msg void OnBnClickedOk();
};
