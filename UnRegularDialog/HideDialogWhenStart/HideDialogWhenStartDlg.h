
// HideDialogWhenStartDlg.h : header file
//

#pragma once


// CHideDialogWhenStartDlg dialog
class CHideDialogWhenStartDlg : public CDialogEx
{
// Construction
public:
	CHideDialogWhenStartDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HIDEDIALOGWHENSTART_DIALOG };

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

private:
	CRect m_rect;
public:
	afx_msg void OnBnClickedCancel();
};
