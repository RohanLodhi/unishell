// Author: Prajas Naik
// This file implements the WindowsInfo class. This class models the 
// Windows Operating System and its main properties, such as OS Name and Kernal Version number
#include "WindowsInfo.h"

using namespace std;


// public constructor: WindowsInfo
//		Default Constructor, Used to get the OS properties on instantiation. 
//		Obtains these using calls to private member function FindOsInformation.
//	@parameters: None
WindowsInfo::WindowsInfo()
{
    mOsName = "";
    mUptime = "";
    mLastBootUpTime = "";
    mKernelVersion = "";
    int result = FindOsInformation();
}

// public accessor functions
string WindowsInfo::GetOsName() const
{
	return mOsName;
}

string WindowsInfo::GetKernelVersion() const
{
    return mKernelVersion;
}

string WindowsInfo::GetUptime()
{
    CalculateUptime();
    return mUptime;
}

// private method function: FindOsInformation
//		It queries WMI using WQL to obtain OS information such as
//		OS Name and Kernal Version and stores them in the private
//		data members mOsName and mKernalVersion
//	@parameters: None
//	@returns: Int value indicating success or failure of the function
int WindowsInfo::FindOsInformation()
{
    HRESULT hres;

    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
        cout << "Failed to initialize COM library. Error code = 0x"
            << hex << hres << endl;
        return 1;                  // Program has failed.
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------

    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        NULL                         // Reserved
    );


    if (FAILED(hres))
    {
        cout << "Failed to initialize security. Error code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return 1;                    // Program has failed.
    }

    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres))
    {
        cout << "Failed to create IWbemLocator object."
            << " Err code = 0x"
            << hex << hres << endl;
        CoUninitialize();
        return 1;                 // Program has failed.
    }

    // Step 4: -----------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    IWbemServices* pSvc = NULL;

    // Connect to the root\cimv2 namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
        NULL,                    // User name. NULL = current user
        NULL,                    // User password. NULL = current
        0,                       // Locale. NULL indicates current
        NULL,                    // Security flags.
        0,                       // Authority (for example, Kerberos)
        0,                       // Context object 
        &pSvc                    // pointer to IWbemServices proxy
    );

    if (FAILED(hres))
    {
        cout << "Could not connect. Error code = 0x"
            << hex << hres << endl;
        pLoc->Release();
        CoUninitialize();
        return 1;                // Program has failed.
    }


    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities 
    );

    if (FAILED(hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }

    // Step 6: --------------------------------------------------
    // The IWbemServices pointer is used to make requests of WMI
    // Here, we query for the Win32_OperatingSystem class

    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_OperatingSystem"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for operating system name failed."
            << " Error code = 0x"
            << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return 1;               // Program has failed.
    }

    // Step 7: -------------------------------------------------
    // Get the data from the query in step 6 -------------------

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator)
    {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
            &pclsObj, &uReturn);

        if (0 == uReturn)
        {
            break;
        }

        VARIANT vtProp;

        VariantInit(&vtProp);

        // Get the value of the Version property of Win32_OperatingSystem
        hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
        mKernelVersion = HelperFunctions::ConvertBstrToString(vtProp.bstrVal);

	// Get the value of the LastBootupTime property of Win32_OperatingSystem
        hr = pclsObj->Get(L"LastBootUpTime", 0, &vtProp, 0, 0);
        mLastBootUpTime = HelperFunctions::ConvertBstrToString(vtProp.bstrVal);

        // Get the value of the Name Property of Win32_OperatingSystem
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        mOsName = HelperFunctions::ConvertBstrToString(vtProp.bstrVal);
        CleanOsName();

        //Cleanup
        VariantClear(&vtProp);
        pclsObj->Release();
    }

    // Cleanup
    // ========

    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();
    return 0;
}


// private method function: CleanOsName
//		It removes unnecessary parts of the mOsName private data member 
//		such as the OS directory.
//	@parameters: None
//	@returns: None
void WindowsInfo::CleanOsName()
{
    string delimiter = "|";
    string token = mOsName.substr(0, mOsName.find(delimiter));
    mOsName = token;
}

// private method function: CalculateUptime
// It queries WMI using WQL to obtain OS information such as
//		the OS system uptime and stores it in the private
//		data members mUptime
//	@param: None
//	@returns: int value indicating success or failure of the function

void WindowsInfo::CalculateUptime()
{
    tm lastBootUpTime = Time::ConvertStringToTm(mLastBootUpTime);
    time_t localTime = time(0);
    tm now = {};
    localtime_s(&now, &localTime);
    double uptimeInScconds = Time::CalculateDifference(&now, &lastBootUpTime);
    mUptime = Time::SecondsToDaysHoursMinutesSeconds(uptimeInScconds);
}

