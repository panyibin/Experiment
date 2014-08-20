// GIFImage.cpp : implementation file
//

#include "stdafx.h"
#include "LoadGIF2.h"
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
END_DHTML_EVENT_MAP()



// CGIFImage message handlers

BOOL CGIFImage::CanAccessExternal()//we overwrite this function to cancel the warning when script calls window.external.somefunc()
{
	return TRUE;
}

BOOL CGIFImage::IsExternalDispatchSafe()//we overwrite this function to cancel the warning when script calls window.external.somefunc()
{
	return TRUE;
}

HRESULT CGIFImage::ShowContextMenu(DWORD /*dwID*/, POINT * /*ppt*/, IUnknown * /*pcmdtReserved*/, IDispatch * /*pdispReserved*/)//hide the context menu of web brwoser control
{
	return S_OK;
}

void CGIFImage::CallJS()
{
	IHTMLDocument2* pDocument;
	HRESULT hr = GetDHtmlDocument(&pDocument);
	IHTMLWindow2* pWindow;
	hr = pDocument->get_parentWindow(&pWindow);

	VARIANT ret;

	ret.vt = VT_EMPTY;

	CString func = L"bad('test')";

	hr = pWindow->execScript(func.AllocSysString(),L"javascript",&ret);
}