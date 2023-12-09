// Author: Prajas Naik
// This file contains the Hardware class. This class represents the Hardware
// of the windows system, and obtains the computer's hardware properties

#pragma once

// Built-in header files
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <lmcons.h>
#include <winsock.h>
#include <iostream>
#include <array>
#include <intrin.h>
#include <comdef.h>
#include <Wbemidl.h>

// Unibash header files
#include "HelperFunctions.h"

// Libraries for inclusion
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "wbemuuid.lib")

// Definitions
#define _WIN32_DCOM
#define STATUS_SUCCESS (0x00000000)


using namespace std;

class Hardware
{
private:

	//Built-in types
	vector<string> mGpuNames;
	string mCpuName;
	string mMemoryUsage;
	string mResolution;
	int mHeight;
	int mWidth;

	//private method function: FindCpuName
	//		It queries WMI using WQL to obtain CPU Name and
	//		stores it in the private data member mCpuName
	//	@param: None
	//	@returns:  int value indicating success or failure 
	//	of the function 	
	int FindCpuName();

	//private method function: FindGpuNames
	//		It queries WMI using WQL to obtain GPU Names and
	//		stores them in the private data member mGpuNames
	//	@param: None
	//	@returns:  int value indicating success or failure 
	//	of the function
	int FindGpuNames();

	//private method function: FindMemoryUsage
	//		Uses the WinAPI GlobalMemoryStatusEx function to
	//		get the total memory and the currently used memory. 
	//		Stores them in the private data member mMemoryUsage
	//	@param: None
	//	@returns:  int value indicating success or failure 
	//	of the function
	int FindMemoryUsage();

	//private method function: FindResolution
	//		Uses the WinAPI GetDesktopWindow and GetWindowRect 
	//		functions to get the height and width of the display. 
	//		Stores them in the private data member mResolution.
	//	@param: None
	//	@returns:  int value indicating success or failure 
	//	of the function 	
	int FindResolution();

public:
	// public constructor: Hardware
	//		It initializes the variables and obtains static
	//		information such as CPU name, GPU Names, and
	//		resolution.
	//	@param: None
	Hardware();

	// public accessor functions
	string GetCpuName();
	vector<string> GetGpuNames();
	string GetMemoryUsage();
	string GetResolution();


	

};

