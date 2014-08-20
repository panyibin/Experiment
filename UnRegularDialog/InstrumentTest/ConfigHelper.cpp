#include "stdafx.h"

#include <MsXml2.h>

#include "SearchClientCommon.h"
#include "constants.h"
#include "ConfigHelper.h"


CConfigHelper::CConfigHelper()
{
}

CConfigHelper::~CConfigHelper()
{
}

HRESULT CConfigHelper::InitialConfigFilePath()
{
    HRESULT hr      = S_OK;
    WCHAR   szFilePath[MAX_PATH] = {0};

    GetFilePath(szFilePath, L"app.config");
    m_csConfigFile = szFilePath;

    return hr;
}

HRESULT CConfigHelper::LoadAppConfig()
{
    return this->LoadAppConfig(m_csConfigFile);
}

HRESULT CConfigHelper::LoadAppConfig(LPCWSTR pwzConfigFileName)
{
    HRESULT                     hr = E_FAIL;
    BOOL                        fRet = TRUE;
    CComPtr<IXMLDOMDocument>    spXmlDoc;
    CComPtr<IXMLDOMNode>        spRootNode;
    CString                     csCheckingDelay;
    CString                     csCheckingInterval;
    INT                         uMillisecondsInMinute = 1000*60;

    if (FAILED(hr = spXmlDoc.CoCreateInstance(__uuidof(DOMDocument))))
    {
        goto Done;
    }

    VARIANT_BOOL fSuccess = false;
    if (FAILED(hr = spXmlDoc->load(CComVariant(pwzConfigFileName), &fSuccess)))
    {
        goto Done;
    }

    if (!fSuccess)
    {
        hr = E_FAIL;
        goto Done;
    }

    //Get the distribution nodes
    if (FAILED(hr = spXmlDoc->selectSingleNode(L"/bing-frame-client-config", &spRootNode)))
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"update-service-url", csUpdateConfigUrl);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"msi-name", csMsiName);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"cab-name", csUpdateCabName);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"exe-full-path", csBingFrameExeFullPath);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"market", csCurrentInstallMarket);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"version", csCurrentInstallVersion);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"culture", csCulture);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"exe-name", csExeName);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"buildtype", csBuildType);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"first-checking-delay", csCheckingDelay);
    if (!fRet)
    {
        goto Done;
    }

    uUpdateStartupCheckingDelay = _wtoi(csCheckingDelay) * uMillisecondsInMinute;

    fRet = GetNodeText(spRootNode, L"checking-interval", csCheckingInterval);
    if (!fRet)
    {
        goto Done;
    }

    uUpdateCheckingInterval = _wtoi(csCheckingInterval) * uMillisecondsInMinute;

    fRet = GetNodeText(spRootNode, L"partner-code", csPartnerCode);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"form-code-mouse", csMouseActivationFormCode);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"form-code-keyboard", csKeyboardActivationFormCode);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"form-code-mouse-AS", csMouseActivationAutosuggestFormCode);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"form-code-keyboard-AS", csKeyboardActivationAutosuggestFormCode);
    if (!fRet)
    {
        goto Done;
    }

    fRet = GetNodeText(spRootNode, L"vertical-url", csVerticalUrl);
    if (!fRet)
    {
        goto Done;
    }

Done:

    if (!fRet)
    {
        hr = E_FAIL;
    }
    return hr;
}

BOOL CConfigHelper::GetNodeText(_In_ IXMLDOMNode* pItem, PCWSTR pwzValueName, CString &csText)
{
    BOOL fResult = FALSE;

    CComPtr<IXMLDOMNode> spNode;
    if (pItem && SUCCEEDED(pItem->selectSingleNode(CComBSTR(pwzValueName), &spNode)))
    {
        CComBSTR bsText;
        if (spNode && SUCCEEDED(spNode->get_text(&bsText)) && bsText)
        {
            csText = bsText;
            fResult = TRUE;
        }
    }
    return fResult;
}

BOOL CConfigHelper::GetFilePath(_Out_z_cap_c_(MAX_PATH) TCHAR* szPath, const TCHAR* c_szFileName)
{
    if (szPath == NULL || c_szFileName == NULL)
    {
        return FALSE;
    }

    TCHAR szPathTemp[MAX_PATH];
    if (!GetModuleFileName(NULL, szPathTemp, MAX_PATH))
    {
        return FALSE;
    }
    
    (_tcsrchr(szPathTemp, '\\'))[1] = '\0';
    _stprintf_s(szPath, MAX_PATH, _TEXT("%s%s"), szPathTemp, c_szFileName);
    return TRUE;
}