#pragma once


#define MAXPROPERTYLENGTH                     1024
#define MAX_REGKEY			4096

#define SYNC_SEND_INSTRUMENTATION_WAIT_TIMEOUT  10000 //wait 10 seconds for the synchronous logging

#define SHOW_FIELDS_LENGTH                  5

#define	CHAR_BACKSLASH		_T('\\')
#define	CHAR_SLASH			_T('/')
#define	CHAR_SEMICOLON		_T(';')
#define	CHAR_EQUAL			_T('=')
#define	CHAR_UNDERSCORE		_T('_')
#define	CHAR_DASH			_T('-')
#define	CHAR_DOT			_T('.')
#define	CHAR_SPACE			_T(' ')
#define	CHAR_COLON			_T(':')
#define	CHAR_NULL			_T('\0')
#define	CHAR_STAR			_T('*')

#define	STRING_EMPTY		_T("")
#define	STRING_CRLF			_T("\r\n")
#define	STRING_STAR			_T("*")
#define	STRING_DASH			_T("-")
#define	STRING_BACKSLASH	_T("\\")
#define	STRING_STARDOTSTAR	_T("*.*")
#define	STRING_DOT			_T(".")
#define	STRING_DOTDOT		_T("..")

const LPTSTR PROPERTY_INSTRUMENTATIONCONFIG = _T("INSTRUMENTATIONCONFIG"); 
const LPTSTR constCustomActionData			= _T("CustomActionData");
const LPTSTR PROPERTY_OSVERSION             = _T("VersionNT"); 
const LPTSTR PROPERTY_OSBUILD               = _T("WindowsBuild"); 
const LPTSTR PROPERTY_PRODUCTVERSION        = _T("PRODUCTVERSION"); 
const LPTSTR PROPERTY_REINSTALL             = _T("REINSTALL"); 
const LPTSTR PROPERTY_SESSIONID             = _T("SESSIONID"); 
const LPTSTR PROPERTY_MARKET                = _T("MARKET"); 
const LPTSTR PROPERTY_BUILDTYPE             = _T("BUILDTYPE");
const LPTSTR PROPERTY_INSTALLDATETIME       = _T("INSTALLDATETIME");
const LPTSTR PROPERTY_ORIGINALINSTALLDATETIME = _T("ORIGINALINSTALLDATETIME");
const LPTSTR PROPERTY_MACHINEID             = _T("MACHINEID");
const LPTSTR PROPERTY_USERID                = _T("MACHINEUSERID");
const LPTSTR PROPERTY_APPEXENAME            = _T("BINGFRAMEEXENAME");
const LPTSTR PROPERTY_TASKBARBANDNAME       = _T("BINGSEARCHBOXDLLNAME");
const LPTSTR PROPERTY_TASKBARBAND64NAME     = _T("BINGSEARCHBOX64DLLNAME");
const LPTSTR PROPERTY_LOCPRODUCTNAME        = _T("LOCPRODUCTNAME");
const LPTSTR PROPERTY_APPEXEPATH            = _T("INSTALLLOCATION");
const LPTSTR PROPERTY_INSTALLERLANGUAGE     = _T("MSILANGUAGE");
const LPTSTR PROPERTY_APPAGE                = _T("AppAge"); 
const LPTSTR PROPERTY_MARKET_VERSION_ERROR_MESSAGE                = _T("MARKET_VERSION_ERROR_MESSAGE"); 
const LPTSTR PROPERTY_ABORTCODE             = _T("AbortCode");
const LPTSTR PROPERTY_ERRORCODE             = _T("ErrorCheckPoint");
const LPTSTR PROPERTY_ENDINSTALL            = _T("ENDINSTALL");
const LPTSTR PROPERTY_REMOVE                = _T("REMOVE");
const LPTSTR PROPERTY_UPDATER               = _T("UPDATER");
const LPTSTR PROPERTY_EXEPROCESSNAME        = _T("EXEPROCESSNAME"); 
const LPTSTR PROPERTY_BINGAPPHOSTEXENAME    = _T("BINGAPPHOSTEXENAME"); 
const LPTSTR PROPERTY_BINGSURROGATENAME     = _T("BINGSURROGATENAME"); 
const LPTSTR PROPERTY_BINGRUNTIMEEXENAME    = _T("BINGRUNTIMEEXENAME"); 
const LPTSTR PROPERTY_BINGEXTHOSTEXENAME    = _T("BINGEXTHOSTEXENAME"); 
const LPTSTR PROPERTY_UPDATECABNAME         = _T("UPDATECABNAME"); 
const LPTSTR PROPERTY_PARTNERCODE           = _T("PARTNERCODE"); 
const LPTSTR PROPERTY_FORMCODEMOUSE         = _T("FORMCODE_MOUSE"); 
const LPTSTR PROPERTY_FORMCODEKEYBOARD      = _T("FORMCODE_KEYBOARD"); 
const LPTSTR PROPERTY_FORMCODEMOUSE_AS      = _T("FORMCODE_MOUSE_AS"); 
const LPTSTR PROPERTY_FORMCODEKEYBOARD_AS   = _T("FORMCODE_KEYBOARD_AS"); 
const LPTSTR PROPERTY_FORMCODEDSE           = _T("FORMCODE_DSE"); 
const LPTSTR PROPERTY_SHOWDHP               = _T("SHOWDHP"); 
const LPTSTR PROPERTY_SHOWDSE               = _T("SHOWDSE"); 
const LPTSTR PROPERTY_SHOWDB                = _T("SHOWDB"); 
const LPTSTR PROPERTY_SHOWSYNCPIC           = _T("SHOWSYNCPIC"); 
const LPTSTR NEWINSTALLTYPE                 = _T("new"); 
const LPTSTR UPGRADEINSTALLTYPE             = _T("upgrade"); 
const LPTSTR STARTTIME                      = _T("StartTime");
const LPTSTR SYNCIMAGE_REGKEY               = _T("dwSettingsEnableSyncBingHomePicture");
const LPTSTR AUTOSET_DHP_REGKEY             = _T("dwSettingsEnableAutoSetDHP");
const LPTSTR AUTOSET_DSE_REGKEY             = _T("dwSettingsEnableAutoSetDSE");
const DWORD SYNCIMAGE_REG_DEFAULTVALUE      = 1;
const DWORD AUTOSET_DHP_REG_DEFAULTVALUE    = 0;
const DWORD AUTOSET_DSE_REG_DEFAULTVALUE    = 0;
const LPTSTR PRIVACY_REGKEY                 = _T("dwSettingsDisablePrivacy");
const LPTSTR FIRSTRUN_PARAMETERS            = _T("/fromkey /firstrun");
const LPTSTR CHINA_SHORTCUT_FOLDERNAME		= _T("必应缤纷桌面");
const LPTSTR DEFAULT_HOMEPAGE               = _T("http://www.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_US			= _T("http://www.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_GB			= _T("http://uk.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_CN            = _T("http://123.bing.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_JP			= _T("http://jp.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_DE			= _T("http://de.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_FR			= _T("http://fr.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_CA			= _T("http://ca.msn.com/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR DEFAULT_HOMEPAGE_AU			= _T("http://ninemsn.com.au/?pc=%s&ocid=bdtdhp&form=BDKTDH&DT=%s");
const LPTSTR FEEDBACK_LINK                  = _T("http://go.microsoft.com/fwlink/?LinkId=285401&clcid=%s");
const LPTSTR PRIVACY_LINK                   = _T("http://go.microsoft.com/fwlink/?LinkId=285395&clcid=%s");

const LPTSTR PROPERTY_INSTALL_SET_DHP       = _T("INSTALL_SET_DHP"); 
const LPTSTR PROPERTY_INSTALL_SET_DSE       = _T("INSTALL_SET_DSE"); 
//################## define taskbar search related constants ##############################
const TCHAR g_lpszREGSVR32PathName32[]      = _T("%windir%\\system32\\");
const TCHAR g_lpszREGSVR32[]                = _T("\\REGSVR32.EXE");

const LPTSTR PROPERTY_SHOWSYNCPIC_IN_PLACE  = _T("SHOW_SYNCPIC_INPLACE");
const LPTSTR PROPERTY_SHOWDB_IN_PLACE       = _T("SHOW_DB_INPLACE");
const LPTSTR PROPERTY_SHOWDHP_IN_PLACE      = _T("SHOW_DHP_INPLACE");
const LPTSTR PROPERTY_SHOWDSE_IN_PLACE      = _T("SHOW_DSE_INPLACE");
const LPTSTR PROPERTY_SHOWPRIVACY_IN_PLACE  = _T("SHOW_PRIVACY_INPLACE");
const LPTSTR PROPERTY_SHOW_MKT_SPECIAL_DHP  = _T("SHOW_MKT_SPECIAL_DHP");
const LPTSTR PROPERTY_SHOW_FIELD_COUNT      = _T("SHOW_FIELDS_COUNT");

const LPTSTR SYNCPIC_CONTROL_TEMPLATE         = _T("SHOWSYNCPIC_%d");
const LPTSTR DB_CONTROL_TEMPLATE              = _T("SHOWDB_%d");
const LPTSTR DHP_CONTROL_TEMPLATE             = _T("SHOWDHP_%d");
const LPTSTR DSE_CONTROL_TEMPLATE             = _T("SHOWDSE_%d");
const LPTSTR PRIVACY_CONTROL_TEMPLATE         = _T("SHOWPrivacy_%d");
const LPTSTR MKT_SPECIAL_DHP_TEMPLATE         = _T("SHOW_MKT_SPECIAL_DHP_%d");

// Instrumentation events ID definition
const DWORD dwEulaAccepted                  = 4;
const DWORD dwInstallStarted                = 11;
const DWORD dwInstallCompleted              = 12;
const DWORD dwInstallFailed                 = 13;
const DWORD dwInstallAborted                = 14;
const DWORD dwInstallOption                 = 15;
const DWORD dwUnInstallStarted              = 31;
const DWORD dwUnInstallCompleted            = 32;
const DWORD dwUnInstallFailed               = 33;
const DWORD BINGFRAME_EXIT_THRESHOLD        = 1000*60;
const DWORD BINGFRAME_STARTUP_THRESHOLD     = 50;

// set Country-Language Code Identifier (CLCID)
// refer to http://msdn.microsoft.com/en-us/goglobal/bb964664.aspx
const LPTSTR INSTALLER_EN_US_CLCID               = _T("0x0409");
const LPTSTR INSTALLER_EN_GB_CLCID               = _T("0x0809");
const LPTSTR INSTALLER_ZH_CN_CLCID               = _T("0x0804");
const LPTSTR INSTALLER_JA_JP_CLCID               = _T("0x0411");
const LPTSTR INSTALLER_DE_DE_CLCID               = _T("0x0407");
const LPTSTR INSTALLER_FR_FR_CLCID               = _T("0x040c");
const LPTSTR INSTALLER_EN_CA_CLCID               = _T("0x1009");
const LPTSTR INSTALLER_EN_AU_CLCID               = _T("0x0c09");

const GEOID CHINA_GEOID                         = 0x2D;
const GEOID AUSTRALIA_GEOID                     = 0xC;

const LPTSTR ZH_CN_MARKET                       = _T("zh-cn");
const LPTSTR EN_AU_MARKET                       = _T("en-au");

const LPTSTR DEFAULT_PACK_OFFER_DLL_NAME        = _T("DefaultPackOffer.dll");

#define InstallerGetMsiProperty(hInstall, szName, szValueBuffer, size)               \
{                                                                                \
	size = sizeof(szValueBuffer) / sizeof(TCHAR);                                \
	if (MsiGetProperty(hInstall, szName, szValueBuffer, &size) != ERROR_SUCCESS) \
{                                                                            \
	hr = E_FAIL;                                                            \
	goto Done;                                                              \
}                                                                            \
}                                                                               \

#define InstallerCheckHr(hrValue)        \
{                                    \
	hr = (hrValue);                  \
	if (hr != S_OK)                  \
{                                \
	goto Done;                   \
}                                \
}                                    \

#define InstallerCheckRet(ret, errValue)       \
{                                          \
	if (ret != ERROR_SUCCESS)              \
{                                      \
	hr = errValue;                     \
	goto Done;                         \
}                                      \
}

#define InstallerFuncStartHr(initVal)	\
	HRESULT hr=(initVal);

#define InstallerChkBool(condition, errValue)	\
	if ((condition) == TRUE)					\
	{											\
		hr = errValue;							\
		goto Done;							\
	}

#define	InstallerStringLength(pszSrc,len)											\
	{																				\
		HRESULT	assume_HR = StringCchLength(pszSrc,STRSAFE_MAX_CCH,(size_t *)&len);	\
		__assume(assume_HR);														\
	}

#define	InstallerStringCchCopy(pszDest,cchDest,pszSrc)				\
	{																\
		HRESULT	assume_HR = StringCchCopy(pszDest,cchDest,pszSrc);	\
		__assume(assume_HR);										\
	}

#define	InstallerStringCchCat(pszDest,cchDest,pszSrc)				\
	{																\
		HRESULT	assume_HR = StringCchCat(pszDest,cchDest,pszSrc);	\
		__assume(assume_HR);										\
	}

#define	InstallerDeleteCArray(anarray)	\
	{									\
		if (anarray)					\
		{								\
			delete []anarray;			\
			anarray=NULL;				\
		}								\
	}