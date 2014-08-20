// Test.cpp : implementation file
//

#include "stdafx.h"
#include "MinimizeWindowTest.h"
#include "Test.h"
#include "afxdialogex.h"


// CTest dialog

IMPLEMENT_DYNAMIC(CTest, CDialogEx)

CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTest::IDD, pParent)
{

}

CTest::~CTest()
{
}

void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTest, CDialogEx)
END_MESSAGE_MAP()


// CTest message handlers
