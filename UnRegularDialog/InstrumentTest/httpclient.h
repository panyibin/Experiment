#ifndef httpclient_h
#define httpclient_h

#include "common/httpdefs.h"

class CHttpClient
{
public:
    CHttpClient();
    ~CHttpClient();
	
    typedef VOID (*RequestCompleteCallback)(_In_ VOID * pvContext);


    HRESULT Initialize(_In_opt_z_ wchar_t * wszUserAgent);
    HRESULT Shutdown();
    HRESULT Get(
        const wchar_t * wszHostName,
        INTERNET_PORT port,
        const wchar_t * wszQuery,
        RequestCompleteCallback fnRequestCompleteCallback,
        _In_ VOID * pvContext);


private:
    struct RequestInfo
    {
        RequestInfo(RequestCompleteCallback fnRequestCompleteCallback, _In_ VOID * pvContext) :
            hConnect(NULL),
            hRequest(NULL),
            fnRequestCompleteCallback(fnRequestCompleteCallback),
            pvContext(pvContext)
        {
        }

        ~RequestInfo()
        {
            CLOSE_INTERNET_HANDLE(hConnect);
            hConnect = NULL;

            CLOSE_INTERNET_HANDLE(hRequest);
            hRequest = NULL;
        }

        HINTERNET                            hConnect;
        HINTERNET                            hRequest;
        CHttpClient::RequestCompleteCallback fnRequestCompleteCallback;
        VOID *                               pvContext;
    };


    static VOID CALLBACK
    HttpRequestStatusCallback(
        _Inout_ HINTERNET hInternet,
        _Inout_ DWORD_PTR dwContext,
        DWORD dwInternetStatus,
        _Inout_ LPVOID lpvStatusInformation,
        DWORD dwStatusInformationLength);


    bool                 m_fInitialized;
    HINTERNET            m_hInternet;
    STATUS_CALLBACK_TYPE m_pfnStatusCallback;
};



#endif  //  httpclient_h
