
// FunctionTestDlg.h : header file
//
#include <functional>

#pragma once


// CFunctionTestDlg dialog
class CFunctionTestDlg : public CDialogEx
{
// Construction
public:
	CFunctionTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FUNCTIONTEST_DIALOG };

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
	//void funcTest(int n, function<int a> x);

	void SetCtlPos(int nID, function<POINT(POINT pt)> posGet);
};
