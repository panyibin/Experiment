#pragma once

#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif 

// CGIFImage dialog

class CGIFImage : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CGIFImage)

public:
	CGIFImage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGIFImage();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_GIFIMAGE, IDH = IDR_HTML_GIFIMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
