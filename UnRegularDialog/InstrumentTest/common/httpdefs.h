#ifndef httpdefs_h
#define httpdefs_h



//
//  Some parts of the code base use the HTTP ATL/MFC classes, which
//  internally use wininet.  This prevents our CHttpClient class from
//  using winhttp because including both wininet.h and winhttp.h
//  causes errors at compile time due to those two libraries
//  attempting to redefine each others' constants.
//
//  However, our CHttpClient class must use winhttp in order to be
//  usable by our updater, which is an NT service: wininet does not
//  work in NT services.
//
//  The right thing to do would be to remove from our code base the
//  dependency on those ATL/MFC classes that use wininet, but we are a
//  bit late in cycle for v1 to do that.
//
//  Instead, we abstract the difference away here and will address
//  this properly in v2.
//
#ifdef _WININET_


#define STATUS_CALLBACK_TYPE                         INTERNET_STATUS_CALLBACK
#define INVALID_STATUS_CALLBACK_VALUE                INTERNET_INVALID_STATUS_CALLBACK
#define SEND_REQUEST_COMPLETE_VALUE                  INTERNET_STATUS_REQUEST_COMPLETE


#define CLOSE_INTERNET_HANDLE(h)                     ::InternetCloseHandle(h)
#define OPEN_HTTP_SESSION(userAgent)                 ::InternetOpen( \
    userAgent,                                                       \
    INTERNET_OPEN_TYPE_PRECONFIG,                                    \
    NULL,                                                            \
    NULL,                                                            \
    INTERNET_FLAG_ASYNC)
#define SET_REQUEST_STATUS_CALLBACK(h, cb)           ::InternetSetStatusCallback( \
    h,                                                                            \
    cb)
#define MAKE_HTTP_CONNECTION(h, host, port)          ::InternetConnect( \
    h,                                                                  \
    host,                                                               \
    port,                                                               \
    NULL,                                                               \
    NULL,                                                               \
    INTERNET_SERVICE_HTTP,                                              \
    0,                                                                  \
    NULL)
#define OPEN_HTTP_REQUEST(h, verb, q, port, context) ::HttpOpenRequest( \
    h,                                                                  \
    verb,                                                               \
    q,                                                                  \
    NULL,                                                               \
    NULL,                                                               \
    NULL,                                                               \
    INTERNET_FLAG_KEEP_CONNECTION |                                     \
    INTERNET_FLAG_DONT_CACHE      |                                     \
    INTERNET_FLAG_PRAGMA_NOCACHE  |                                     \
    (port == 443 ? INTERNET_FLAG_SECURE : 0),                           \
    (DWORD_PTR) context)
#define SEND_HTTP_REQUEST(h, context)                ::HttpSendRequest(h, NULL, 0, NULL, 0)


#else  //  _WININET_


#include <winhttp.h>

#define STATUS_CALLBACK_TYPE                         WINHTTP_STATUS_CALLBACK
#define INVALID_STATUS_CALLBACK_VALUE                WINHTTP_INVALID_STATUS_CALLBACK
#define SEND_REQUEST_COMPLETE_VALUE                  WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE


#define CLOSE_INTERNET_HANDLE(h)                     ::WinHttpCloseHandle(h)
#define OPEN_HTTP_SESSION(userAgent)                 ::WinHttpOpen( \
    wszUserAgent,                                                   \
    WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,                              \
    WINHTTP_NO_PROXY_NAME,                                          \
    WINHTTP_NO_PROXY_BYPASS,                                        \
    WINHTTP_FLAG_ASYNC)
#define SET_REQUEST_STATUS_CALLBACK(h, cb)           ::WinHttpSetStatusCallback( \
    h,                                                                           \
    cb,                                                                          \
    WINHTTP_CALLBACK_FLAG_ALL_COMPLETIONS,                                       \
    0)
#define MAKE_HTTP_CONNECTION(h, host, port)          ::WinHttpConnect(h, host, port, 0)
#define OPEN_HTTP_REQUEST(h, verb, q, port, context) ::WinHttpOpenRequest( \
    h,                                                                     \
    verb,                                                                  \
    q,                                                                     \
    NULL,                                                                  \
    WINHTTP_NO_REFERER,                                                    \
    WINHTTP_DEFAULT_ACCEPT_TYPES,                                          \
    WINHTTP_FLAG_REFRESH | (port == 443 ? WINHTTP_FLAG_SECURE : 0))
#define SEND_HTTP_REQUEST(h, context)                ::WinHttpSendRequest( \
    h,                                                                     \
    WINHTTP_NO_ADDITIONAL_HEADERS,                                         \
    0,                                                                     \
    WINHTTP_NO_REQUEST_DATA,                                               \
    0,                                                                     \
    0,                                                                     \
    (DWORD_PTR) context)

#endif  //  _WININET_


#endif  //  httpdefs_h
