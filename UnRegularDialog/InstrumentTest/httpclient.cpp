#include "stdafx.h"
#include <atldef.h>
#include "httpclient.h"



using namespace std;



CHttpClient::CHttpClient() :
    m_fInitialized(false),
    m_hInternet(NULL),
    m_pfnStatusCallback(NULL)
{
}



CHttpClient::~CHttpClient()
{
    ATLASSERT(m_hInternet == NULL);
}



HRESULT
CHttpClient::Initialize(_In_opt_z_ wchar_t * wszUserAgent)
{
    HRESULT hr;


    ATLASSERT(m_fInitialized == false);


    m_hInternet = OPEN_HTTP_SESSION(wszUserAgent);
    if (m_hInternet == NULL)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    m_pfnStatusCallback = SET_REQUEST_STATUS_CALLBACK(m_hInternet, CHttpClient::HttpRequestStatusCallback);
    if (m_pfnStatusCallback != NULL)
    {
        //
        //  The return value of ::WinHttpSetStatusCallback() is the
        //  previous status callback, if any, for the request.  Since
        //  we just created this request, having a pre-existing status
        //  callback before we've set ours would be weird.
        //
        ATLASSERT(false);
        hr = E_FAIL;
        goto Done;
    }

    if (m_pfnStatusCallback == INVALID_STATUS_CALLBACK_VALUE)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    m_fInitialized = true;
    hr = S_OK;


Done:

    return hr;
}



HRESULT
CHttpClient::Shutdown()
{
    HRESULT hr;


    if (!m_fInitialized)
    {
        hr = S_OK;
        goto Done;
    }

    ATLASSERT(m_hInternet != NULL);    
    if (m_hInternet != NULL)
    {
        CLOSE_INTERNET_HANDLE(m_hInternet);
        m_hInternet = NULL;
    }

    m_fInitialized = false;
    hr = S_OK;


Done:

    return hr;
}



HRESULT
CHttpClient::Get(
    const wchar_t * wszHostName,
    INTERNET_PORT port,
    const wchar_t * wszQuery,
    RequestCompleteCallback fnRequestCompleteCallback,
    _In_ VOID * pvContext)
{
    HRESULT                    hr;
    CHttpClient::RequestInfo * pri = NULL;
    BOOL                       br;

	CFile file;


    if (!m_fInitialized)
    {
        hr = E_UNEXPECTED;
        goto Done;
    }

    pri = new CHttpClient::RequestInfo(fnRequestCompleteCallback, pvContext);
    if (pri == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Done;
    }

    pri->hConnect = MAKE_HTTP_CONNECTION(m_hInternet, wszHostName, port);
    if (pri->hConnect == NULL)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    pri->hRequest = OPEN_HTTP_REQUEST(pri->hConnect, L"GET", wszQuery, port, pri);
    if (pri->hRequest == NULL)
    {
        hr = HRESULT_FROM_WIN32(::GetLastError());
        goto Done;
    }

    br = SEND_HTTP_REQUEST(pri->hRequest, pri);
    if (!br)
    {
        DWORD dwErr = ::GetLastError();
        if (dwErr != ERROR_IO_PENDING)
        {
            hr = HRESULT_FROM_WIN32(dwErr);
            goto Done;
        }
    }

	br = WinHttpReceiveResponse(pri->hRequest,NULL);

	const int BYTES_READ = 512;


	BYTE buf[BYTES_READ + 1];
	DWORD bytesRead = 0;

	if(file.Open(L"d:\\myTest.txt",CFile::modeCreate|CFile::modeWrite))
	{
		if(WinHttpReadData(pri->hRequest,buf,BYTES_READ,&bytesRead))
		{

			while (bytesRead)
			{
				file.Write(buf,bytesRead);
				WinHttpReadData(pri->hRequest,buf,BYTES_READ,&bytesRead);
			}

		}
		else
		{
			DWORD err = GetLastError();
			//TRACE1("%s\n",)
		}
	}

    pri = NULL;  //  The async callback now owns the memory.
    hr  = S_OK;


Done:

    delete pri;
    pri = NULL;

    return hr;
}



VOID CALLBACK
CHttpClient::HttpRequestStatusCallback(
    _Inout_ HINTERNET hInternet,
    _Inout_ DWORD_PTR dwContext,
    DWORD dwInternetStatus,
    _Inout_ LPVOID lpvStatusInformation,
    DWORD dwStatusInformationLength)
{
    CHttpClient::RequestInfo * requestinfo;


    //
    //  Keep the compiler happy.
    //
    hInternet                 = NULL;
    lpvStatusInformation      = NULL;
    dwStatusInformationLength = NULL;


    //
    //  Our CHttpClient::RequestInfo structure will be passed to each
    //  invocation of this callback, so extract it now.
    //
    requestinfo = (CHttpClient::RequestInfo *) dwContext;
    if (requestinfo == NULL)
    {
        ATLASSERT(false);  //  does this ever happen?
		return;
    }


    //
    //  Our HTTP client class is tailored for issuing instrumentation
    //  pings, so we are never interested in consuming the response
    //  from the server.  Thus, we just watch for the request to be
    //  complete so that we can delete the request info structure that
    //  we created when the request was issued.
    //
    if (dwInternetStatus == SEND_REQUEST_COMPLETE_VALUE)
    {
        if (requestinfo->fnRequestCompleteCallback != NULL)
        {
            requestinfo->fnRequestCompleteCallback(requestinfo->pvContext);
        }

        delete requestinfo;
    }

    return;
}
