// ATLInstrumentTest.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "ATLInstrumentTest_i.h"



class CATLInstrumentTestModule : public ATL::CAtlExeModuleT< CATLInstrumentTestModule >
	{
public :
	DECLARE_LIBID(LIBID_ATLInstrumentTestLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLINSTRUMENTTEST, "{3DF9B30B-2FDD-452A-84B5-A5273CA6EEBA}")
	};

CATLInstrumentTestModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

