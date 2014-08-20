#pragma once

#include <atlcoll.h>
#include <atlcomcli.h>

#include <WinInet.h>
#include "httpclient.h"

/*
  Example usage:

   CInstrumentation * pinst = CInstrumentation::GetInstance();
   if (!pinst)
   {
       hr = E_OUTOFMEMORY;
       goto Done;
   }

   pinst->Initialize(L"instrumentation.config");
   pinst->LogEvent(7, L"app-specific-name", L"app-specific-value");
*/



class CInstrumentation
{
public:

	static CInstrumentation* GetInstance();

    HRESULT InitializeFromConfigFile(_In_z_ wchar_t * wszConfigFileName, _In_z_ BSTR bstrMachineId);
    HRESULT InitializeFromXmlString(_In_z_ BSTR bstrConfigXml, _In_z_ BSTR bstrMachineId);

    HRESULT LogEvent(DWORD dwEventId);
    HRESULT LogEvent(DWORD dwEventId, const wchar_t * wszName, const wchar_t * wszValue);

    HRESULT SynchronousLogEvent(DWORD dwEventId, DWORD dwTimeout = INFINITE);
    HRESULT SynchronousLogEvent(DWORD dwEventId, _In_z_ wchar_t * wszName, _In_z_ wchar_t * wszValue, DWORD dwTimeout = SYNC_CALLBACK_WAIT_THRESHOLD);

    HRESULT StartMultiPartEvent(DWORD dwEventId);
    HRESULT ContinueMultiPartEvent(const wchar_t * wszName, const wchar_t * wszValue);
    HRESULT LogMultiPartEvent();
    HRESULT SynchronousLogMultiPartEvent(DWORD dwTimeout = INFINITE);

    void SetPrivacyEnabled(BOOL bEnable);

	HRESULT AddFlightInfoToBaseUrl(const wchar_t * flightName, const wchar_t * flightRevision);

    enum EventType
    {
        // For BingFrame app.
        FirstRun              = 1,
        BingFrameLaunch       = 2,
        DailyPing             = 3,
        EulaAccept            = 4,
        Activate              = 5, // Bing bar shows off
        DoSearch              = 6, // User issues a search

        // For installer.
        InstallStart          = 11,
        InstallSuccess        = 12,
        InstallFail           = 13,
        InstallAbort          = 14,

        // For updater.
        UpdateCheck           = 21,
        UpdateShouldUpgrade   = 22,
        UpdateDownloadSuccess = 23,
        UpdateInstallStart    = 24,

		// For BD v1.1
		ContentSearchNews		= 35,
		ContentSearchPopnow		= 36,
		ContentSearchImage		= 37,
		ContentSearchVideo		= 38,
		SetWallPaper			= 39,
		ContentTileHide			= 40,
		ContentTileUnhide		= 41,
		MoveSearchbox			= 42,
		PickColorSkin			= 43,
		ShowCopiedText			= 44,
		SearchCopiedText		= 45,
		ContentTabShow			= 46,
		WallPaperPanelShow		= 47,
		PickLocation			= 48,
		OpenLinkInAbout			= 49,
		OpenMainHelp			= 50,
		ClickJumplist			= 51,
		ClickBingLogo			= 52,
		ClickMinimizeTile		= 53,
		HistoryFunctionEnable	= 54,
		HistoryClear			= 55,
		DragToSearch			= 56,

		// For BD v1.2
		FacebookPanelShow		= 60,
		AutoFBSignin			= 61,
		ClickFBPrivacy			= 62,
		NewsFeedPanelShow		= 63,
		ClickTabsOnFBPage		= 64,
		ClickViewAll			= 65,
		ClickLinkOnNewsFeed		= 66,
		ClickLinkUnderTabs		= 67,
		ClickPhotos				= 68,
		ClickUsername			= 69,
		ClickEditProfile		= 70,
		ClickLogout				= 71,

		SearchWithToolbar	= 84,
		ClickIconOnToolbar	= 85,
		ClickSearchButton	= 86,
		SearchWithoutQuery = 87,
		LeftClickBDinSystemtray	= 88,
		RightClickBDinSystemtray =	89,
		ClickIteminSystemTray	=90,
		ClickDictAs				= 91,
		ClickDictClose			= 92,
		ClickLinkOnDictPage		= 93,
		UseDictScroll			= 94,

		ViewWallpaper          =  97,
		WallpaperPageup_down	= 98,
		SetSyncWallpaper		=	99,

		SearchInline			= 100,
		highlight               = 101,
		ClickOnSearchInlineButton =102,
		InlinePanelShow          =103,	
		ClickOnItemInInlinePanel =104,
		CloseTheInlinePanel      =106,

		// setting instrumentations
        ChooseUserModesFromSetting      = 80,
        ChooseCopyPaste                 = 79,
        ChooseAutoPopup                 = 78,
        ChooseAutoLaunch                = 75,
        ChooseExpandMode                = 74,
        ClickTabsOnSettingPanel         = 73,
        SettingPanelShow                = 72,
        ShortcutKeyFunctionSetting      = 81,

        // v1.3
        UserComtpuerInfo                = 107,
		ShowRichAS                = 108,
		DisableWallpaperSetting = 109, //Todo,bruce: need double check the num is not used
		FailToDownloadWallpaper = 110,
		MoveTheInliePanel		= 111,

		//v1.3.x
		ClickVoiceSearchButton = 112,
		VoiceSearchMicFail	= 113,
		VoiceSearchNetworkFail = 114,
		VoiceSearchClickRetry = 115,
		VoiceSearchClickMicSetting = 116,
		VoiceSearchOpenBrowserSuccess  = 117,
		VoiceSearchNotRecognize = 118,

		//local search
		ShowLResultInAll			=120,
		ClickLResultStringInAll		=121,
		ClickLResultFolderInAll		=127,
		ClickLResultStringInLocal	=122,
		ClickLocalTab				=123,
		ShowLNoResult				=124,
		ClickMoreLResult			=125,
		ClickLResultFolder			=126,

		//v1.3.2
		ClickImageStoryInWPPanel	=127,

		//instant answer
		UserFoldInstantAnswer		=128,
		UserUnfoldInstantAnswer		=129,
		InstantAnswerSuccessEnable	=130,
		InstantAnswerShow			=131,
		ClickOnItemInInstantAnswer	=132,

		//browser
		ClickRestoreBtn			=132,
		ClickBackBtn			=133,
		DbClickToMaxmize		=134,
		DbClickToNormal			=135,
		OpenCurrentInDefaultBrowser	=136,
		CopyCurrentLinkToClipboard	=137,
		ClickMenuItemRestore = 138,
		BrowserPosMoved = 139,
		BrowserSizeChanged = 140,
		NavigateToBing = 141,
		NavigateToNonBing = 142,
		ClickCloseBtn = 143,
		ShowSearchBoxInTaskbar = 144,
		HotkeyToSwitchMode = 153,

		//bing defend
		AutoSetDSE = 145,
		AutoSetDHP = 146,
		DSEChanged = 147,
		DHPChanged = 148,
		SetBackDSESuccess = 149,
		SetBackDHPSuccess = 150,
		SetBackDSEFail = 151,
		SetBackDHPFail = 152,

		// Please keep the events in CN version below 600.
		// For global version events start with 601.
		ChooseSerachboxPopnow	= 602,
		SearchGrayPopnow		= 603
    };

    enum
    {
        DailyPingInterval = 24 * 3600 * 1000
    };

    static const int SYNC_CALLBACK_WAIT_THRESHOLD = 2000;  // 2 seconds to wait for the sync http request call back

private:
	CInstrumentation();
	~CInstrumentation();

private:
    struct EventRecord
    {
        EventRecord() :
            fHasNameValues(false),
            dwEventId(0)
        {
        }

        CComBSTR bstrUrl;
        bool     fHasNameValues;
        DWORD    dwEventId;
    };


    static VOID SyncHttpRequestCompleteCallback(_In_ VOID * pvContext);
    static VOID AsyncHttpRequestCompleteCallback(_In_ VOID * pvContext);


    HRESULT Initialize(_In_ IXMLDOMDocument * pxmldoc, _In_ BSTR bstrMachineId);
    VOID    AsyncHttpRequestCompleteCallbackInternal();
    HRESULT FetchHost(_In_ IXMLDOMDocument * pxmldoc);
    HRESULT FetchPort(_In_ IXMLDOMDocument * pxmldoc);
    HRESULT FetchUrlBase(_In_ IXMLDOMDocument * pxmldoc);
    HRESULT FormatUrlBase();
    HRESULT BuildEvent(DWORD dwEventId, _Out_ EventRecord ** pper);
    HRESULT BuildEvent(DWORD dwEventId, const wchar_t * wszName, const wchar_t * wszValue, _Out_ EventRecord ** pper);
    HRESULT LogEventInternal(_In_opt_ EventRecord * per);
    HRESULT SynchronousLogEventInternal(_In_opt_ EventRecord * per, DWORD dwTimeout = SYNC_CALLBACK_WAIT_THRESHOLD);
    HRESULT AddNameValueToEvent(_In_opt_ EventRecord * per, const wchar_t * wszName, const wchar_t * wszValue);
    HRESULT UrlEscapeString(const wchar_t * wszIn, _Out_ BSTR * pbstrOut);

private:
    bool                    m_fInitialized;
    BOOL                    m_bPrivacyEnabled;
    CHttpClient			    m_httpClient;
    CComBSTR                m_bstrHost;
    WORD                    m_wPort;
    CComBSTR                m_bstrUrlBase;
    CAtlList<EventRecord *> m_listEvents;
    CRITICAL_SECTION        m_cs;
    unsigned int            m_uiNumRequestsPending;
    EventRecord *           m_pEventRecord;
    CComBSTR                m_bstrMachineId;
 

	static CComAutoCriticalSection m_critSect;
	static CInstrumentation* m_pInstance;
};
