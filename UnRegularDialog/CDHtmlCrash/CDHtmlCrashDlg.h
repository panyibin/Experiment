
// CDHtmlCrashDlg.h : header file
//

#pragma once

#include "DHtmlTest.h"


// CCDHtmlCrashDlg dialog
class CCDHtmlCrashDlg : public CDialogEx
{
// Construction
public:
	CCDHtmlCrashDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CDHTMLCRASH_DIALOG };

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
	afx_msg void OnBnClickedGotoSite1();
	afx_msg void OnBnClickedGotoSite2();
	afx_msg void OnBnClickedGotoSite3();

	CDHtmlTest* m_pCDhtmlTest;
};
