#include "stdafx.h"
//#include <bldver.h>
#include <atlstr.h>
#include <msxml6.h>
#include "instrumentation.h"
#include "constants.h"
#include "ConfigHelper.h"
#include "common/common.h"

const TCHAR REG_SETTINGS_STARTTIME[] =                      _T("StartTime");

CInstrumentation* CInstrumentation::m_pInstance = NULL;
CComAutoCriticalSection CInstrumentation::m_critSect;

CInstrumentation::CInstrumentation() :
    m_fInitialized(false),
    m_bPrivacyEnabled(true),
    m_wPort(0),
    m_uiNumRequestsPending(0),
    m_pEventRecord(NULL)
{
    ::InitializeCriticalSection(&m_cs);
	m_httpClient.Initialize(NULL);
}

CInstrumentation* CInstrumentation::GetInstance()
{
	if(!m_pInstance)
	{
		m_critSect.Lock();
		if(!m_pInstance)
		{
			m_pInstance = new CInstrumentation;
		}
		m_critSect.Unlock();
	}
	ATLASSERT(m_pInstance != NULL);
	return m_pInstance;
}

CInstrumentation::~CInstrumentation()
{
    ATLASSERT(m_pEventRecord == NULL);

	delete m_pInstance;
	m_pInstance = NULL;

    ::DeleteCriticalSection(&m_cs);
}


HRESULT
CInstrumentation::InitializeFromConfigFile(_In_z_ wchar_t * wszConfigFileName, _In_z_ BSTR bstrMachineId)
{
    HRESULT                   hr;
    CComPtr<IXMLDOMDocument2> spxmldoc;
    VARIANT_BOOL              vtboolResult;


    ATLASSERT(m_fInitialized == false);


    //
    //  Load up the config file.
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

    hr = spxmldoc->load(CComVariant(wszConfigFileName), &vtboolResult);
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
    //  Initialize with the config from config file
    //
    hr = this->Initialize(spxmldoc, bstrMachineId);
    if (hr != S_OK)
    {
        goto Done;
    }


Done:

    return hr;
}



HRESULT
CInstrumentation::InitializeFromXmlString(_In_z_ BSTR bstrConfigXml, _In_z_ BSTR bstrMachineId)
{
    HRESULT                   hr;
    CComPtr<IXMLDOMDocument2> spxmldoc;
    VARIANT_BOOL              vtboolResult;


    ATLASSERT(m_fInitialized == false);


    //
    //  Load up the config xml string.
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

    hr = spxmldoc->loadXML(bstrConfigXml, &vtboolResult);
    if (hr != S_OK)
    {
        goto Done;
    }

    if (vtboolResult != VARIANT_TRUE)
    {
        hr = E_FAIL;
        goto Done;
    }

    hr = this->Initialize(spxmldoc, bstrMachineId);
    if (hr != S_OK)
    {
        goto Done;
    }


Done:

    return hr;
}



HRESULT
CInstrumentation::Initialize(_In_ IXMLDOMDocument * pxmldoc, _In_ BSTR bstrMachineId)
{
    HRESULT hr;


    ATLASSERT(m_fInitialized == false);


    //
    //  Assign the machine id.
    //
    ATLASSERT(bstrMachineId != NULL);
    m_bstrMachineId = bstrMachineId;
    if (m_bstrMachineId == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }


    //
    //  Fetch the particulars from the config xml.
    //
    hr = this->FetchHost(pxmldoc);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = this->FetchPort(pxmldoc);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = this->FetchUrlBase(pxmldoc);
    if (hr != S_OK)
    {
        goto Done;
    }

    //
    //  We're ready to go.
    //
    m_fInitialized = true;


Done:

    return hr;
}

HRESULT
CInstrumentation::LogEvent(DWORD dwEventId)
{
    HRESULT       hr;
    EventRecord * per = NULL;
    CComBSTR      bstrUrl;


    ATLASSERT(m_fInitialized);


    hr = BuildEvent(dwEventId, &per);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = LogEventInternal(per);
    if (hr == S_OK)
    {
        per = NULL;
        goto Done;
    }

    if (hr == S_FALSE)
    {
        //
        //  LogEventInternal() uses S_FALSE to tell us to delete the
        //  event record, but we don't want this bubbling up to the
        //  caller.  Since per remains non-null, it will get deleted,
        //  so we'll thunk hr to S_OK to keep the caller happy.
        //
        hr = S_OK;
    }


Done:

    delete per;
    per = NULL;

    return hr;
}



HRESULT
CInstrumentation::LogEvent(DWORD dwEventId, const wchar_t * wszName, const wchar_t * wszValue)
{
    HRESULT       hr;
    EventRecord * per = NULL;


    hr = BuildEvent(dwEventId, wszName, wszValue, &per);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = LogEventInternal(per);
    if (hr == S_OK)
    {
        per = NULL;
        goto Done;
    }

    if (hr == S_FALSE)
    {
        //
        //  LogEventInternal() uses S_FALSE to tell us to delete the
        //  event record, but we don't want this bubbling up to the
        //  caller.  Since per remains non-null, it will get deleted,
        //  so we'll thunk hr to S_OK to keep the caller happy.
        //
        hr = S_OK;
    }


Done:

    delete per;
    per = NULL;

    return hr;
}



HRESULT
CInstrumentation::SynchronousLogEvent(DWORD dwEventId, DWORD dwTimeout)
{
    HRESULT       hr;
    EventRecord * per = NULL;


    ATLASSERT(m_fInitialized);


    hr = BuildEvent(dwEventId, &per);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = SynchronousLogEventInternal(per, dwTimeout);


Done:

    delete per;
    per = NULL;

    return hr;
}



HRESULT
CInstrumentation::SynchronousLogEvent(DWORD dwEventId, _In_z_ wchar_t * wszName, _In_z_ wchar_t * wszValue, DWORD dwTimeout)
{
    HRESULT       hr;
    EventRecord * per = NULL;


    ATLASSERT(m_fInitialized);


    hr = BuildEvent(dwEventId, wszName, wszValue, &per);
    if (hr != S_OK)
    {
        goto Done;
    }

    hr = SynchronousLogEventInternal(per, dwTimeout);


Done:

    delete per;
    per = NULL;

    return hr;
}



HRESULT
CInstrumentation::StartMultiPartEvent(DWORD dwEventId)
{
    HRESULT hr;


    //
    //  If we are starting to log a multi-part event, the event record
    //  should be null.  It is non-null only when we are in the midst
    //  of logging a multi-part event, in which case, only the methods
    //  ContinueMultiPartEvent() and LogMultiPartEvent() should be
    //  called.
    //
    ATLASSERT(m_pEventRecord == NULL);


    hr = BuildEvent(dwEventId, &m_pEventRecord);
    if (hr != S_OK)
    {
        goto Done;
    }


Done:

    return hr;
}



HRESULT
CInstrumentation::ContinueMultiPartEvent(const wchar_t * wszName, const wchar_t * wszValue)
{
    HRESULT hr;


    ATLASSERT(m_pEventRecord != NULL);


    hr = AddNameValueToEvent(m_pEventRecord, wszName, wszValue);
    if (hr != S_OK)
    {
        goto Done;
    }


Done:

    return hr;
}



HRESULT
CInstrumentation::LogMultiPartEvent()
{
    HRESULT hr;


    ATLASSERT(m_pEventRecord != NULL);


    hr = LogEventInternal(m_pEventRecord);
    if (hr == S_OK)
    {
        m_pEventRecord = NULL;
        goto Done;
    }

    if (hr == S_FALSE)
    {
        //
        //  LogEventInternal() uses S_FALSE to tell us to delete the
        //  event record, but we don't want this bubbling up to the
        //  caller.  Since per remains non-null, it will get deleted,
        //  so we'll thunk hr to S_OK to keep the caller happy.
        //
        hr = S_OK;
    }


Done:

    delete m_pEventRecord;
    m_pEventRecord = NULL;

    return hr;
}



HRESULT
CInstrumentation::SynchronousLogMultiPartEvent(DWORD dwTimeout)
{
    HRESULT hr;

    ATLASSERT(m_pEventRecord != NULL);

    hr = SynchronousLogEventInternal(m_pEventRecord, dwTimeout);

    delete m_pEventRecord;
    m_pEventRecord = NULL;

    return hr;
}



VOID
CInstrumentation::SyncHttpRequestCompleteCallback(VOID * pvContext)
{
    ::SetEvent((HANDLE) pvContext);
}



VOID
CInstrumentation::AsyncHttpRequestCompleteCallback(VOID * pvContext)
{
    ((CInstrumentation *) pvContext)->AsyncHttpRequestCompleteCallbackInternal();
}



VOID
CInstrumentation::AsyncHttpRequestCompleteCallbackInternal()
{
    HRESULT       hr;
    EventRecord * per     = NULL;
    bool          flocked = false;

    ::EnterCriticalSection(&m_cs);

	ATLASSERT(m_uiNumRequestsPending > 0);

    flocked = true;

    m_uiNumRequestsPending--;
    if (m_listEvents.IsEmpty())
    {
        goto Done;
    }

    per = m_listEvents.RemoveHead();
    hr = m_httpClient.Get(
        m_bstrHost,
        m_wPort,
        per->bstrUrl,
        CInstrumentation::AsyncHttpRequestCompleteCallback,
        this);
    if (hr != S_OK)
    {
        goto Done;
    }

    m_uiNumRequestsPending++;


Done:

    delete per;
    per = NULL;

    if (flocked)
    {
        ::LeaveCriticalSection(&m_cs);
        flocked = false;
    }
}


HRESULT
CInstrumentation::FetchHost(_In_ IXMLDOMDocument * pxmldoc)
{
    HRESULT              hr;
    CComPtr<IXMLDOMNode> spnode;


    hr = pxmldoc->selectSingleNode(CComBSTR(L"/instrumentation-config/host"), &spnode);
    if ((hr != S_OK) && (hr != S_FALSE))
    {
        goto Done;
    }

    if (hr == S_OK)
    {
        hr = spnode->get_text(&m_bstrHost);
        if (hr != S_OK)
        {
            goto Done;
        }
    }

    if (hr == S_FALSE)
    {
        //
        //  Missing <host> tag -- default to localhost.
        //
        m_bstrHost = L"localhost";
        hr         = S_OK;
    }


Done:

    return hr;
}



HRESULT
CInstrumentation::FetchPort(_In_ IXMLDOMDocument * pxmldoc)
{
    HRESULT              hr;
    CComPtr<IXMLDOMNode> spnode;
    CComBSTR             bstrPort;


    hr = pxmldoc->selectSingleNode(CComBSTR(L"/instrumentation-config/port"), &spnode);
    if ((hr != S_OK) && (hr != S_FALSE))
    {
        goto Done;
    }

    if (hr == S_OK)
    {
        hr = spnode->get_text(&bstrPort);
        if (hr != S_OK)
        {
            goto Done;
        }

        m_wPort = (WORD) ::_wtoi(bstrPort);
        if (m_wPort == 0)
        {
            hr = E_INVALIDARG;
            goto Done;
        }
    }

    else if (hr == S_FALSE)
    {
        //
        //  Missing <port> tag -- default to 80.
        //
        m_wPort = 80;
        hr      = S_OK;
    }


Done:

    return hr;
}



HRESULT
CInstrumentation::FetchUrlBase(_In_ IXMLDOMDocument * pxmldoc)
{
    HRESULT              hr;
    CComPtr<IXMLDOMNode> spnode;


    hr = pxmldoc->selectSingleNode(CComBSTR(L"/instrumentation-config/urlbase"), &spnode);
    if ((hr != S_OK) && (hr != S_FALSE))
    {
        goto Done;
    }

    if (hr == S_OK)
    {
        hr = spnode->get_text(&m_bstrUrlBase);
        if (hr != S_OK)
        {
            goto Done;
        }
    }

    else if (hr == S_FALSE)
    {
        m_bstrUrlBase = L"/specify-urlbase-in-config-file";
        if (m_bstrUrlBase == NULL)
        {
            hr = E_OUTOFMEMORY;
            goto Done;
        }

        hr = S_OK;
    }

    hr = this->FormatUrlBase();


Done:

    return hr;
}



HRESULT
CInstrumentation::FormatUrlBase()
{
    HRESULT        hr;
    CString        strUrl;
    BOOL           br;
    OSVERSIONINFO  osvi = { 0 };
    CString        strOsVer;
    CConfigHelper  configHelper;


    //
    //  CComBSTR does not have a replace function, so we'll copy into
    //  a CString, perform our substitutions, and copy it back.
    //
    strUrl = m_bstrUrlBase;


    //
    //  Hardcoded machine id for now.
    //
    strUrl.Replace(L"[MachineId]", m_bstrMachineId);


    //
    //  If it's calling from installer, AppVer/Market/Distribution will be replaced alread, and installer might
    //  not be able to read the config file.
    //  And for the subsequent calls after installtion, load config should success to fetch AppVer/Market/Distribution
    //
    if (strUrl.Find(L"[AppVer]") != -1
        || strUrl.Find(L"[Market]") != -1
        || strUrl.Find(L"[Distribution]") != -1
        || strUrl.Find(L"[BuildType]") != -1)
    {

        //
        //  Our version, market, and distribution channel are in the updater config.
        //
        hr = configHelper.InitialConfigFilePath();
        if (hr != S_OK)
        {
            goto Done;
        }

        hr = configHelper.LoadAppConfig();
        if (hr != S_OK)
        {
            goto Done;
        }

        strUrl.Replace(L"[AppVer]", configHelper.csCurrentInstallVersion);
        strUrl.Replace(L"[Market]", configHelper.csCurrentInstallMarket);
        strUrl.Replace(L"[Distribution]", configHelper.csPartnerCode);
        strUrl.Replace(L"[BuildType]", configHelper.csBuildType);
    }

    //
    //  Operating system version.
    //
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    br = ::GetVersionEx(&osvi);
    if (br == FALSE)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    strOsVer.Format(L"%d.%d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
    strUrl.Replace(L"[OsVer]", strOsVer);

    //
    //  Copy it back.
    //
    m_bstrUrlBase = strUrl;
    if (m_bstrUrlBase == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    hr = S_OK;

Done:

    return hr;
}

HRESULT
CInstrumentation::BuildEvent(DWORD dwEventId, _Out_ EventRecord ** pper)
{
    HRESULT         hr;
    EventRecord *   per = NULL;
    CString         strEventId;
    CString         strUrl;
    CString         appAge;
    FILETIME        fileTime;
    ULONGLONG       ulStartTime = 0;
    ULARGE_INTEGER  currentTime;
    ULONG           uRet;
    CRegKey         key;

    //
    //  Create and initialize the event record.
    //
    per = new EventRecord();
    if (per == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }


    //
    //  Format the request.
    //
    strEventId.Format(L"%d", dwEventId);
    strUrl = m_bstrUrlBase;

    strUrl.Replace(L"[EventId]", strEventId);

    //
    //  App age
    //
    GetSystemTimeAsFileTime(&fileTime);
    currentTime.HighPart = fileTime.dwHighDateTime;
    currentTime.LowPart = fileTime.dwLowDateTime;

    uRet = key.Open(HKEY_LOCAL_MACHINE, REG_ROOT, KEY_READ);
    if (uRet == ERROR_SUCCESS)
    {
        //
        //  If we can open the reg key, query the intall time,
        //  if not, ignore it, with this, the app age value won't be set.
        //
        uRet = key.QueryQWORDValue(REG_SETTINGS_STARTTIME, ulStartTime);

        if( uRet == ERROR_SUCCESS)
        {
            if (currentTime.QuadPart < ulStartTime)
            {
                //
                //  The current time is not always bigger than the install time, 
                //  user might change the system time
                //  At that case, set the appAge to -1
                //
                appAge.Format(L"%d", -1);
            }
            else
            {
                appAge.Format(L"%d", (currentTime.QuadPart - ulStartTime) / APP_AGE_FACTOR);
            }

            strUrl.Replace(L"[AppAge]", appAge);
        }
    }

    per->bstrUrl = strUrl;
    if (per->bstrUrl == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    per->dwEventId = dwEventId;

    //
    //  All is well, so pass up the event.
    //
    *pper = per;
    per   = NULL;
    hr    = S_OK;


Done:

    delete per;
    per = NULL;

    return hr;
}



HRESULT
CInstrumentation::BuildEvent(DWORD dwEventId, const wchar_t * wszName, const wchar_t * wszValue, _Out_ EventRecord ** pper)
{
    HRESULT       hr;
    EventRecord * per = NULL;


    hr = BuildEvent(dwEventId, &per);
    if (hr != S_OK)
    {
        goto Done;
    }

    ATLASSERT(per != NULL);

    hr = AddNameValueToEvent(per, wszName, wszValue);
    if (hr != S_OK)
    {
        goto Done;
    }

    *pper = per;
    per   = NULL;
    hr    = S_OK;


Done:

    delete per;
    per = NULL;

    return hr;
}



HRESULT
CInstrumentation::LogEventInternal(_In_opt_ EventRecord * per)
{
    // check whether we should send instrumentation data based on setting
    // always send event 1(FirstRun), 2(BingDesktopRun), 3(DailyPing)
    ATLASSERT(per->dwEventId != 0);
    if(!m_bPrivacyEnabled && per->dwEventId > 3)
    {
        // return S_FALSE to tell the caller to delete per
        return S_FALSE;
    }

    HRESULT hr;
    bool    flocked = false;


    //
    //  Conditionally enqueue the event.
    //
    //  The reason we do this is to guarantee that instrumentation
    //  events are issued in the order that the calls were made into
    //  the instrumentation API.  Since our HTTP requests are async, a
    //  very rapid sequence of instrumentation calls do not have a
    //  deterministic order in which they are actually sent by the
    //  networking layer.  This would confuse our analytics.
    //
    //  We could solve this by making our HTTP requests synchronous,
    //  but that is a non-starter because the sending of
    //  instrumentation pings cannot be allowed to interfere with the
    //  performance of the app.
    //
    //  Instead, we specify a completion callback that the HTTP client
    //  invokes when the request has completed.  That completion
    //  callback is responsible for issuing the next request, and the
    //  callback specifies itself as the completion routine.  This
    //  allows us to chain the requests such that they happen in the
    //  order in which they were queued while also satisfying the
    //  requirement that this happen in the background.
    //
	
    ::EnterCriticalSection(&m_cs);
    flocked = true;

    if (m_uiNumRequestsPending == 0)
    {
		if(!per)
		{
			hr = S_FALSE;
			goto Done;
		}

        hr = m_httpClient.Get(
			m_bstrHost,
            m_wPort,
			per->bstrUrl,
            CInstrumentation::AsyncHttpRequestCompleteCallback,
            this);

        if (hr != S_OK)
        {
            goto Done;
        }

        m_uiNumRequestsPending++;
        hr = S_FALSE;  //  Indicates to the caller that it should deallocate the event record.
    }

    else
    {
        m_listEvents.AddTail(per);
        hr = S_OK;
    }


Done:

    if (flocked)
    {
        ::LeaveCriticalSection(&m_cs);
        flocked = false;
    }

    return hr;
}



HRESULT
CInstrumentation::SynchronousLogEventInternal(_In_opt_ EventRecord * per, DWORD dwTimeout)
{
    HRESULT hr;
    HANDLE  hRequestCompleteEvent = NULL;
    DWORD   dwWaitResult;


    //
    //  Create the event that the callback will signal when the
    //  request completes.
    //
    hRequestCompleteEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hRequestCompleteEvent == NULL)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }


    //
    //  Issue the request, then wait on the event -- our completion
    //  routine is responsible for setting the event, which will
    //  release us from the wait.
    //
    hr = m_httpClient.Get(
        m_bstrHost,
        m_wPort,
        per->bstrUrl,
        CInstrumentation::SyncHttpRequestCompleteCallback,
        hRequestCompleteEvent);
    if (hr != S_OK)
    {
        goto Done;
    }

    dwWaitResult = ::WaitForSingleObject(hRequestCompleteEvent, dwTimeout);
    if (dwWaitResult != WAIT_OBJECT_0)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    hr = S_OK;


Done:

    if (hRequestCompleteEvent != NULL)
    {
        ::CloseHandle(hRequestCompleteEvent);
        hRequestCompleteEvent = NULL;
    }

    return hr;
}


HRESULT
	CInstrumentation::AddFlightInfoToBaseUrl(const wchar_t * flightName, const wchar_t * flightRevision)
{
	HRESULT  hr = S_FALSE;
	CString  strUrl;
	CComBSTR bstr;

	// check params
	if (flightName == NULL || flightRevision == NULL)
	{
		ATLASSERT(false && L"Params should not be null.");
		goto Done;
	}

	//
	//  CComBSTR's don't have the string processing methods we need,
	//  but CString's do, so copy it over.
	//
	strUrl = m_bstrUrlBase;

	// check if attributes are already added
	int StartPos = strUrl.Find(L"|fl");
	if (StartPos != -1)
	{
		// remove the old fl to add the new fl
		strUrl = strUrl.Mid(0, StartPos);
	}

	// flight name
	strUrl.Append(L"|fl");
	hr = UrlEscapeString(flightName, &bstr);
	if (hr != S_OK)
	{
		goto Done;
	}
	strUrl.Append(bstr);
	bstr.Empty();

	// flight revision
	strUrl.Append(L"|fr");
	hr = UrlEscapeString(flightRevision, &bstr);
	if (hr != S_OK)
	{
		goto Done;
	}
	strUrl.Append(bstr);
	bstr.Empty();

	m_bstrUrlBase = strUrl;
	if (m_bstrUrlBase == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto Done;
	}

	hr = S_OK;


Done:

	return hr;
}


HRESULT
CInstrumentation::AddNameValueToEvent(_In_opt_ EventRecord * per, const wchar_t * wszName, const wchar_t * wszValue)
{
    HRESULT  hr;
    CString  strUrl;
    CComBSTR bstr;

	if(!per)
	{
		hr = S_FALSE;
		goto Done;
	}

    //
    //  CComBSTR's don't have the string processing methods we need,
    //  but CString's do, so copy it over.
    //
    strUrl = per->bstrUrl;


    //
    //  Name/value pairs are stored within the kv value, but the kv
    //  value is not put into the request string unless the event has
    //  at least one name/value pair.  Here, we determine whether we
    //  are the first and thus need to do that append.
    //
    if (per->fHasNameValues == false)
    {
        //
        //  This must be the first name/value pair added to this event.
        //
        strUrl.Append(L"|kv");
        per->fHasNameValues = true;
    }

    else
    {
        //
        //  Subsequent name/value pairs are separated from each other
        //  by a comma, so for every pair after the first, we must
        //  tack that on.
        //
        strUrl.Append(L",");
    }

    hr = UrlEscapeString(wszName, &bstr);
    if (hr != S_OK)
    {
        goto Done;
    }

    strUrl.Append(bstr);
    bstr.Empty();

    strUrl.Append(L":");
    hr = UrlEscapeString(wszValue, &bstr);
    if (hr != S_OK)
    {
        goto Done;
    }

    strUrl.Append(bstr);
    bstr.Empty();

    per->bstrUrl = strUrl;
    if (per->bstrUrl == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    hr = S_OK;


Done:

    return hr;
}



HRESULT
CInstrumentation::UrlEscapeString(const wchar_t * wszIn, _Out_ BSTR * pbstrOut)
{
    HRESULT  hr;
    wchar_t  wszOut[MAX_PATH] = { 0 };
    DWORD    dwLen            = sizeof(wszOut) / sizeof(wchar_t);
    CComBSTR bstrOut;


    hr = ::UrlEscape(wszIn, wszOut, &dwLen, URL_ESCAPE_PERCENT);
    if (hr != S_OK)
    {
        goto Done;
    }

    bstrOut = wszOut;
    if (bstrOut == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    *pbstrOut = bstrOut.Detach();
    hr = S_OK;


Done:

    return hr;
}

void CInstrumentation::SetPrivacyEnabled(BOOL bEnable)
{
    m_bPrivacyEnabled = bEnable;
}