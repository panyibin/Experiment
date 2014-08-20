// ConfigFileMgr.h : Declaration of the CConfigFileMgr
// UpdateManager

#pragma once

#include <sal.h>

class CConfigHelper
{

public:
    CConfigHelper();
    ~CConfigHelper();

    HRESULT InitialConfigFilePath();
    HRESULT LoadAppConfig();
    HRESULT LoadAppConfig(LPCWSTR pwzConfigFileName);
    BOOL GetNodeText(_In_ IXMLDOMNode* pItem, PCWSTR pwzValueName, CString &csText);

private:
    BOOL GetFilePath(_Out_z_cap_c_(MAX_PATH) TCHAR* szPath, const TCHAR* c_szFileName);

public:
    CString csUpdateConfigUrl;
    CString csMsiName;
    CString csUpdateCabName;
    CString csBingFrameExeFullPath;
    CString csCurrentInstallMarket;
    CString csCurrentInstallVersion;
    CString csExeName;
    CString csBuildType;
    CString csCulture;
    CString csPartnerCode;
    CString csMouseActivationFormCode;
    CString csKeyboardActivationFormCode;
    CString csMouseActivationAutosuggestFormCode;
    CString csKeyboardActivationAutosuggestFormCode;
    INT     uUpdateCheckingInterval;
    INT     uUpdateStartupCheckingDelay;
    HANDLE  m_hTimer;
    CString csVerticalUrl;

private:
    CString m_csConfigFile;
};