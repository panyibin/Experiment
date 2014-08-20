
// HideDialogWhenStart.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHideDialogWhenStartApp:
// See HideDialogWhenStart.cpp for the implementation of this class
//

class CHideDialogWhenStartApp : public CWinApp
{
public:
	CHideDialogWhenStartApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CHideDialogWhenStartApp theApp;