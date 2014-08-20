// SearchClientCommon.h : Definitions common to many Search Client apps
// These are all defined in one place to avoid name collisions and/or misspellings
// $Id: SearchClientCommon.h#1 2011/05/11 12:17:11 REDMOND\\garymcco $

#pragma once

// AppIDs
#define APPID_BINGFRAME_UPDATER     L"Updater"

// File systems value, names and paths
#define FILE_ROOT_CSIDL     CSIDL_COMMON_APPDATA
#define FILE_ROOT_FOLDER    L"Microsoft\\" PRODUCT_NAME

// Search Client error and success codes
#define FACILITY_SEARCH_CLIENT  79

#define S_NOT_MODIFIED      MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_SEARCH_CLIENT, 1)
#define S_RETRY_NEEDED      MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_SEARCH_CLIENT, 2)
#define S_PENDING           MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_SEARCH_CLIENT, 3)

#define E_SHUTDOWN_APP      MAKE_HRESULT(SEVERITY_ERROR,   FACILITY_SEARCH_CLIENT, 4)

inline HRESULT SafeSysAllocStringPtr(_Out_ BSTR *dest, const WCHAR *src)
{
    HRESULT hr = S_OK;
    if (dest)
    {
        SysFreeString(*dest);
        *dest = SysAllocString(src);
        if (*dest == NULL)
            hr = E_OUTOFMEMORY;
    }
    return hr;
}