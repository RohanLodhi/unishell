// Author: Prajas Naik
// This file implements the Hardware class. This class represents the Hardware
// of the windows system, and obtains the computer's hardware properties
#include "Hardware.h"

using namespace std;

// public constructor: Hardware
//		It initializes the variables and obtains static
//		information such as CPU name, GPU Names, and
//		resolution.
//	@param: None
Hardware::Hardware()
{
    mCpuName = "";
    mGpuNames;
    mMemoryUsage = "";
    mWidth = 0;
    mHeight = 0;
    mResolution = "";
    FindCpuName();
    FindGpuNames();
    FindResolution();
}

// public accessor functions
string Hardware::GetCpuName()
{
    return mCpuName;
}

string Hardware::GetResolution()
{
    return mResolution;
}

string Hardware::GetMemoryUsage()
{
    FindMemoryUsage();
    return mMemoryUsage;
}
vector<string> Hardware::GetGpuNames()
{
    return mGpuNames;
}

//private method function: FindCpuName
//		It queries WMI using WQL to obtain CPU Name and
//		stores it in the private data member mCpuName
//	@param: None
//	@returns:  int value indicating success or failure 
//	of the function 	
int Hardware::FindCpuName()
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
    // Use the IWbemServices pointer to make requests of WMI ----
    // Here, it gets the name of the CPU
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_Processor"),
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
        // Get the value of the Name property
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        mCpuName = HelperFunctions::ConvertBstrToString(vtProp.bstrVal);
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

//private method function: FindMemoryUsage
//		Uses the WinAPI GlobalMemoryStatusEx function to
//		get the total memory and the currently used memory. 
//		Stores them in the private data member mMemoryUsage
//	@param: None
//	@returns:  int value indicating success or failure 
//	of the function
int Hardware::FindMemoryUsage()
{
    try
    {
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(memoryStatus);
        GlobalMemoryStatusEx(&memoryStatus); //using WinAPI to get the memory status
        long totalMemory = (long)(memoryStatus.ullTotalPhys / 1024 / 1024); //divide by 1024 * 1024 to convert to MiB
        long currentlyUtilizedMemory = totalMemory - (long)(memoryStatus.ullAvailPhys / 1024 / 1024); //divide by 1024 * 1024 to convert to MiB
        mMemoryUsage = to_string(currentlyUtilizedMemory) + "MiB / " + to_string(totalMemory) + "MiB";
        return 0;
    }
    catch (...)
    {
        cout << "Error occurred";
        return 1; //error
    }
}

//private method function: FindResolution
//		Uses the WinAPI GetDesktopWindow and GetWindowRect 
//		functions to get the height and width of the display. 
//		Stores them in the private data member mResolution.
//	@param: None
//	@returns:  int value indicating success or failure 
//	of the function 	
int Hardware::FindResolution()
{
    try
    {
        RECT desktop;
        const HWND hDesktop = GetDesktopWindow(); //using WinAPI to get desktop window
        GetWindowRect(hDesktop, &desktop); //using WinAPI to store the height and width of the desktop in desktop variable
        mWidth = desktop.right;
        mHeight = desktop.bottom;
        if (mWidth == NULL && mHeight == NULL)
            return 0;
        mResolution = to_string(mWidth) + "x" + to_string(mHeight);
        return 1; //error
    }
    catch (...)
    {
        cout << "Error occurred";
        return 1;//error
    }

}

//private method function: FindGpuNames
//		It queries WMI using WQL to obtain GPU Names and
//		stores them in the private data member mGpuNames
//	@param: None
//	@returns:  int value indicating success or failure 
//	of the function
int Hardware::FindGpuNames()
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
    // Use the IWbemServices pointer to make requests of WMI ----

    // For example, get the names of the graphics cards
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_VideoController"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres))
    {
        cout << "Query for graphics card name failed."
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
        // Get the value of the Name property
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        mGpuNames.push_back(HelperFunctions::ConvertBstrToString(vtProp.bstrVal));

        // Cleanup
        VariantClear(&vtProp);
        pclsObj->Release();
    }

    // Cleanup
    // ========

    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();

    return 0;   // Program successfully completed.

}


