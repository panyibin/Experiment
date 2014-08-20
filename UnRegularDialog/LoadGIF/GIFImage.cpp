// GIFImage.cpp : implementation file
//

#include "stdafx.h"
#include "LoadGIF.h"
#include "GIFImage.h"


// CGIFImage dialog

IMPLEMENT_DYNCREATE(CGIFImage, CDHtmlDialog)

CGIFImage::CGIFImage(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CGIFImage::IDD, CGIFImage::IDH, pParent)
{

}

CGIFImage::~CGIFImage()
{
}

void CGIFImage::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CGIFImage::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CGIFImage, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CGIFImage)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CGIFImage message handlers

HRESULT CGIFImage::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CGIFImage::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
