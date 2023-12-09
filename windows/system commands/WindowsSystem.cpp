// Author: Prajas Naik
// This file implements the WindowsSystem class. This class models the Windows System
#include "WindowsSystem.h"
#include "WindowsInfo.h"

using namespace std;

// Default Constructor
WindowsSystem :: WindowsSystem()
{
    mUserName = "not defined";
    mComputerModel = "";
    mDevice = Hardware();
    mWindows = WindowsInfo();
    FindComputerModel();
    //GetHostName();
    FindUsername();
    
}

//private method function: FindUserName
//		Uses the WinAPI GetUserNameA function to obtain the username
//	@param: None
//	@returns: int value to indicate either success or failure
int WindowsSystem::FindUsername()
{
    if (mUserName == "not defined")
    {
        try
        {
            char userNameBuffer[UNLEN + 1];
            DWORD bufferLength = UNLEN + 1;
            bool result = GetUserNameA(userNameBuffer, &bufferLength); //Using GetUserNameA function of WinAPI
            mUserName = userNameBuffer;
            if (result)
                return 0;
            else return 1;
        }
        catch (...)
        {
            cout << "Some error occurred";
            return 1;
        }

    }
    else
    {
        cout << mUserName << endl;
        return 0;
    }
}


// private method function: GetComputerModel
//		It queries WMI using WQL to obtain Computer Model and
//		stores it in the private data member mComputerModel
//	@param: None
//	@returns: int value to indicate either success or failure
int WindowsSystem::FindComputerModel()
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
    // Here, we query for the Win32_ComputerSystem class

    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_ComputerSystem"),
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

        // Get the value of the Model and Manufacturer property of Win32_ComputerSystem


        hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
        mComputerModel = HelperFunctions::ConvertBstrToString(vtProp.bstrVal);

        hr = pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
        mComputerModel += " " + HelperFunctions::ConvertBstrToString(vtProp.bstrVal);

        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        mHostName = HelperFunctions::ConvertBstrToString(vtProp.bstrVal);
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


//public method function: WhoAmI
//		Uses WinAPI to obtain the username of the current user
//	@params: None
//	@returns: int value to indicate either success or failure
int WindowsSystem::WhoAmI() 
{
    cout << endl << mUserName << endl;
    return 0;
}


//public method function: NeoFetch
//		Displays System Information, such as CPU Name, GPU Name, 
//		Resolution, etc. Similar functionality to neofetch 
//		command on Linux
//	@params: None
//	@returns: int value to indicate either success or failure
int WindowsSystem::NeoFetch()
{
    cout << endl << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " << mUserName << "@" << mHostName << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " << "-------------------------" << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " <<"OS: " << mWindows.GetOsName() << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " <<"Host: " << mComputerModel << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " <<"Kernel: " << mWindows.GetKernelVersion() << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " << "Uptime: " << mWindows.GetUptime() << endl;
    cout << "                                    " <<"Shell: " << mShellName << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " << "Resolution: " << mDevice.GetResolution() << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " <<"CPU: " << mDevice.GetCpuName() << endl;
    for (auto x : mDevice.GetGpuNames())
        cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " <<"GPU: " << x << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " <<"Memory: " << mDevice.GetMemoryUsage() << endl;
    cout << "EEEEEEEEEEEEEEE  EEEEEEEEEEEEEEE    " << endl;
    return 0;
}

//private method function: FindHostName
//		Uses the WinAPI gethostname function to obtain the system host name
//	@params: None
//	@returns: int value to indicate either success or failure
int WindowsSystem::FindHostName()
{
    char name[UNLEN + 1];
    int nameLen = 0;
    gethostname(name, nameLen); // Using WinAPI gethostname function to get system host name
    if (name != NULL)
    {
        mHostName = string(name);
        return 0;
    }
    return 1;
}

