// Author: Prajas Naik
// Contains the declaration for WindowsInfo class. This class
// is used to represent the Windows Operating System and its
// properties.

#pragma once

// Built-in header files
#include <string>
#include <iostream>
#include <comdef.h>
#include <winsock.h>
#include <Wbemidl.h>
#include <ctime>
#include <string>

// Unibash header files
#include "HelperFunctions.h"
#include "Time.h"

// Libraries to link during compilation
#pragma comment(lib, "Ws2_32.lib") 
#pragma comment(lib, "wbemuuid.lib")

// Definitions
#define _WIN32_DCOM

using namespace std;


class WindowsInfo
{
private:
	string mOsName;
	string mKernelVersion;
	string mUptime;
	string mLastBootUpTime;
	
	
	// private method function: FindOsInformation
	//		It queries WMI using WQL to obtain OS information such as
	//		OS Name and Kernal Version and stores them in the private
	//		data members mOsName and mKernalVersion
	//	@param: None
	//	@returns: int value indicating success or failure of the function
	int FindOsInformation();

	// private method function: CleanOsName
	//		It removes unnecessary parts of the mOsName private data member 
	//		such as the OS directory.
	//	@param: None
	//	@returns: None
	void CleanOsName();

	// private method function: CalculateUptime
	// It queries WMI using WQL to obtain OS information such as
	//		the OS system uptime and stores it in the private
	//		data members mUptime
	//	@param: None
	//	@returns: int value indicating success or failure of the function
	// 
	void CalculateUptime();
public:
	// public constructor: WindowsInfo
	//		Default Constructor, Used to get the OS properties on instantiation. 
	//		Obtains these using calls to private member function FindOsInformation.
	//	@param: None
	WindowsInfo();

	// public Accessor Function

	string GetOsName() const;
	string GetKernelVersion() const;
	string GetUptime();
};



