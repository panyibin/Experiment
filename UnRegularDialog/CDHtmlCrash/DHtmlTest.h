#pragma once

#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif 

// CDHtmlTest dialog

class CDHtmlTest : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CDHtmlTest)

public:
	CDHtmlTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDHtmlTest();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_DHTMLTEST, IDH = IDR_HTML_DHTMLTEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
