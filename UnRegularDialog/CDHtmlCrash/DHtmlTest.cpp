// DHtmlTest.cpp : implementation file
//

#include "stdafx.h"
#include "CDHtmlCrash.h"
#include "DHtmlTest.h"


// CDHtmlTest dialog

IMPLEMENT_DYNCREATE(CDHtmlTest, CDHtmlDialog)

CDHtmlTest::CDHtmlTest(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CDHtmlTest::IDD, CDHtmlTest::IDH, pParent)
{

}

CDHtmlTest::~CDHtmlTest()
{
}

void CDHtmlTest::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CDHtmlTest::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CDHtmlTest, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CDHtmlTest)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CDHtmlTest message handlers

HRESULT CDHtmlTest::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CDHtmlTest::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
