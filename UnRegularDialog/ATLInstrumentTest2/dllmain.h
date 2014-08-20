// dllmain.h : Declaration of module class.

class CATLInstrumentTest2Module : public ATL::CAtlDllModuleT< CATLInstrumentTest2Module >
{
public :
	DECLARE_LIBID(LIBID_ATLInstrumentTest2Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLINSTRUMENTTEST2, "{A50E6F17-3E88-4A9E-8BB1-A03BDBECE261}")
};

extern class CATLInstrumentTest2Module _AtlModule;
