
// LoadGIF2Dlg.h : header file
//

#pragma once
#include "GIFImage.h"

// CLoadGIF2Dlg dialog
class CLoadGIF2Dlg : public CDialogEx
{
// Construction
public:
	CLoadGIF2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LOADGIF2_DIALOG };

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
	afx_msg void OnBnClickedOk();

	CGIFImage* m_gif;
	afx_msg void OnBnClickedCallJS();

	CStatic m_test;
};
