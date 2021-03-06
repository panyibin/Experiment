
// MinimizeWindowTestDlg.h : header file
//

#pragma once
#include "Test.h"


// CMinimizeWindowTestDlg dialog
class CMinimizeWindowTestDlg : public CDialogEx
{
// Construction
public:
	CMinimizeWindowTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MINIMIZEWINDOWTEST_DIALOG };

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

	CTest* m_test;
};
