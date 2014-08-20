#ifndef common_h
#define common_h



#define PRODUCT_NAME                L"BingDesktop"
#define LOCAL_APPDATA_SUBDIRECTORY  L"\\Microsoft\\" PRODUCT_NAME
#define REG_ROOT                    L"Software\\Microsoft\\" PRODUCT_NAME
#define REG_UPDATER                 REG_ROOT L"\\Updater"


#define MACHINE_ID_CONFIG_FILENAME  L"machine-id.config"
#define MACHINE_ID_XML_ELEMENT_NAME L"machine-id"
#define MACHINE_ID_XPATH_SELECTOR   L"/" MACHINE_ID_XML_ELEMENT_NAME
#define MACHINE_ID_OPEN_XML         L"<" MACHINE_ID_XML_ELEMENT_NAME L">"
#define MACHINE_ID_CLOSE_XML        L"</" MACHINE_ID_XML_ELEMENT_NAME L">"


#define USER_ID_CONFIG_FILENAME     L"user-id.config"
#define USER_ID_XML_ELEMENT_NAME    L"user-id"
#define USER_ID_XPATH_SELECTOR      L"/" USER_ID_XML_ELEMENT_NAME
#define USER_ID_OPEN_XML            L"<" USER_ID_XML_ELEMENT_NAME L">"
#define USER_ID_CLOSE_XML           L"</" USER_ID_XML_ELEMENT_NAME L">"

const ULONGLONG APP_AGE_FACTOR = 864000000000;   //24 hour in 100 billisecond


#endif  //  common_h
