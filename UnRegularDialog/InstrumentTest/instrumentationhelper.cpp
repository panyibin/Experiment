#include "stdafx.h"
#include "instrumentationhelper.h"
#include "common/common.h"
#include "constants.h"

#include <ShlObj.h>
//#include <bldver.h>
#include <msxml6.h>


HRESULT
InstrumentationHelper::LoadMachineSpecificId(_Out_ BSTR * pbstrMachineId, BOOL fLoadPathFromReg)
{
    HRESULT                   hr;
    wchar_t *                 wszPath               = NULL;
    DWORD                     dwLen                 = MAX_PATH;
    INT                       nRet;
    CComBSTR                  bstrMachineIdFilePath;
    CComPtr<IXMLDOMDocument2> spxmldoc;
    VARIANT_BOOL              vtboolResult;
    CComPtr<IXMLDOMNode>      spnode;


    //
    //  The machine ID is generated at install time and stored in the
    //  install folder in a file called machine-id.config.  Here, we
    //  compose the full path to that file.
    //
    wszPath = new wchar_t [MAX_PATH];
    if (wszPath == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    if (fLoadPathFromReg)
    {
        CRegKey  key;
        HKEY     hKeyParent = HKEY_LOCAL_MACHINE;
        nRet = key.Open(hKeyParent, REG_UPDATER, KEY_READ);
        InstallerCheckRet(nRet, E_FAIL);

        nRet = key.QueryStringValue(L"ConfigFile", wszPath, &dwLen);
        if (nRet != ERROR_SUCCESS || dwLen > MAX_PATH)
        {
            hr = E_FAIL;
            goto Done;
        }
    }

    else
    {
        dwLen = ::GetModuleFileName(NULL, wszPath, MAX_PATH);
        if (dwLen == 0)
        {
            hr = HRESULT_FROM_WIN32(::GetLastError());
            goto Done;
        }
    }

    nRet = ::PathRemoveFileSpec(wszPath);
    if (nRet == 0)
    {
        hr = E_FAIL;
        goto Done;
    }

    bstrMachineIdFilePath.Attach(::SysAllocString(wszPath));
    if (bstrMachineIdFilePath == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    bstrMachineIdFilePath += L"\\";
    bstrMachineIdFilePath += MACHINE_ID_CONFIG_FILENAME;
    if (bstrMachineIdFilePath == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }


    //
    //  The file is formatted as XML, so load it up.
    //
    hr = ::CoCreateInstance(
        CLSID_DOMDocument60,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IXMLDOMDocument2,
        reinterpret_cast<VOID **>(&spxmldoc));
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = spxmldoc->load(CComVariant(bstrMachineIdFilePath), &vtboolResult);
    if (hr != S_OK)
    {
        goto Done;
    }

    if (vtboolResult != VARIANT_TRUE)
    {
        hr = E_FAIL;
        goto Done;
    }


    //
    //  Parse out the value of the machine-id tag.
    //
    hr = spxmldoc->selectSingleNode(CComBSTR(MACHINE_ID_XPATH_SELECTOR), &spnode);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = spnode->get_text(pbstrMachineId);


Done:

    delete [] wszPath;
    wszPath = NULL;

    return hr;
}


HRESULT
InstrumentationHelper::LoadUserSpecificId(_Out_ BSTR * pbstrUserId, BOOL fCreateIfNoExistence)
{
    HRESULT                   hr;
	WCHAR                     wszLocalAppDataPath[MAX_PATH];
    CComBSTR                  bstrUserIdFilePath;
    BOOL                      br;
    CComPtr<IXMLDOMDocument2> spxmldoc;
    VARIANT_BOOL              vtboolResult;
    CComPtr<IXMLDOMNode>      spnode;


    //
    //  The machine ID is generated at install time and stored in the
    //  install folder in a file called machine-id.config.  Here, we
    //  compose the full path to that file.
    //
	
	hr = ::SHGetFolderPath(0, CSIDL_LOCAL_APPDATA, NULL, 0, wszLocalAppDataPath);
    if (hr != S_OK)
    {
        goto Done;
    }

    bstrUserIdFilePath = wszLocalAppDataPath;
    bstrUserIdFilePath += LOCAL_APPDATA_SUBDIRECTORY;
    bstrUserIdFilePath += L"\\";
    bstrUserIdFilePath += USER_ID_CONFIG_FILENAME;
    if (bstrUserIdFilePath == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }


    //
    //  The primary user (i.e., the user that installed the product)
    //  will have had their user ID config file created at install
    //  time.  Secondary users (i.e., anyone else who logs into this
    //  machine after the product has been installed) will not have
    //  this file, so we must detect that condition and create the id
    //  and the file now.
    //
    br = ::PathFileExists(bstrUserIdFilePath);
    if (br == FALSE)
    {
        if (!fCreateIfNoExistence)
        {
            hr = E_FAIL;
            goto Done;
        }

        hr = CreateUserId(bstrUserIdFilePath);
        if (hr != S_OK)
        {
            //
            //  For now, we'll be really aggressive and just fail,
            //  however, we may decide later to go ahead and run
            //  without being able to create the id.  Being aggressive
            //  and failing in this case should be ok because being
            //  unable to create the id should be extremely rare.
            //
            goto Done;
        }
    }


    //
    //  By this time, we should have a valid user id stored in:
    //
    //      c:\users\samik\appdata\local\microsoft\bingdesktop\user-id.config
    //
    //
    //  The file is formatted as XML, so load it up.
    //
    hr = ::CoCreateInstance(
        CLSID_DOMDocument60,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IXMLDOMDocument2,
        reinterpret_cast<VOID **>(&spxmldoc));
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = spxmldoc->load(CComVariant(bstrUserIdFilePath), &vtboolResult);
    if (hr != S_OK)
    {
        goto Done;
    }

    if (vtboolResult != VARIANT_TRUE)
    {
        hr = E_FAIL;
        goto Done;
    }


    //
    //  Parse out the value of the machine-id tag.
    //
    hr = spxmldoc->selectSingleNode(CComBSTR(USER_ID_XPATH_SELECTOR), &spnode);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = spnode->get_text(pbstrUserId);


Done:

    return hr;
}

HRESULT
InstrumentationHelper::CreateUserId(_In_z_ BSTR bstrUserIdFilePath)
{
    HRESULT   hr;
    GUID      guid;
    wchar_t * wszGuid   = NULL;
    CStringA  strUserId;
    CStringA  strUserIdXml;
    HANDLE    hFile     = INVALID_HANDLE_VALUE;
    BOOL      bRet;
    DWORD     dwWritten = 0;


    //
    //  For reasons relating to processing in Cosmos, we want these
    //  ids to be a GUID but without the intervening dashes.  So this
    //  isn't ok:
    //
    //      429b21a6-0d4f-4676-a844-a697f82caaa9
    //
    //
    //  But this is:
    //
    //      429b21a60d4f4676a844a697f82caaa9
    //
    hr = ::CoCreateGuid(&guid);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = ::StringFromCLSID(guid, &wszGuid);
    if (hr != S_OK)
    {
        goto Done;
    }

    strUserId = wszGuid;
    strUserId.Replace("{", "");
    strUserId.Replace("}", "");
    strUserId.Replace("-", "");


    //
    //  To make the user id more convenient to consume from its file
    //  on disk, we'll format as XML.
    //
    strUserIdXml = USER_ID_OPEN_XML;
    strUserIdXml += strUserId;
    strUserIdXml += USER_ID_CLOSE_XML;


    //
    //  Finally, write it to disk.
    //
    hFile = ::CreateFile(bstrUserIdFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    bRet = ::WriteFile(hFile, strUserIdXml.GetBuffer(), strUserIdXml.GetLength(), &dwWritten, NULL);
    if (bRet == FALSE)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    if (dwWritten != (DWORD) strUserIdXml.GetLength())
    {
        hr = E_FAIL;
        goto Done;
    }

    hr = S_OK;


Done:

    ::CoTaskMemFree(wszGuid);
    wszGuid = NULL;

    if (hFile != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }

    return hr;
}

