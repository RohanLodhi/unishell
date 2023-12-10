// Author: Prajas Naik
// This file contains the WindowsSystem class as descibed below

#pragma once

// Built-in header files
#include <string>
#include <vector>
#include <lmcons.h>
#include <Windows.h>

// Unibash header files
#include "WindowsInfo.h"
#include "Hardware.h"
#include "HelperFunctions.h"
#include "System.h"
// Libraries to include during compilation
#pragma comment(lib, "wbemuuid.lib")

using namespace std;


// WindowsSystem Class models the Windows System. It has both 
// hardware and software properties relevant to the system. 
class WindowsSystem : public System
{
private:

	//Built-in types
	string mUserName;
	string mHostName;
	string mComputerModel;
	const string mShellName = "unibash 1.0";

	//User-defined types
	Hardware mDevice;
	WindowsInfo mWindows;

	//private method function: FindHostName
	//		Uses the WinAPI FindHostName function to obtain the system host name
	//	@param: None
	//	@returns: int value to indicate either success or failure
	int FindHostName();


	//private method function: FindUserName
	//		Uses the WinAPI GetUserNameA function to obtain the username
	//	@param: None
	//	@returns: int value to indicate either success or failure
	int FindUsername();

	// private method function: GetComputerModel
	//		It queries WMI using WQL to obtain Computer Model and
	//		stores it in the private data member mComputerModel
	//	@param: None
	//	@returns: int value to indicate either success or failure
	int FindComputerModel();

public:
	//Constructor for Windows System class
	WindowsSystem();

	//public method function: WhoAmI
	//		Uses WinAPI to obtain the username of the current user
	//	@param: None
	//	@returns: int value to indicate either success or failure
	int WhoAmI();

	//public method function: NeoFetch
	//		Displays System Information, such as CPU Name, GPU Name, 
	//		Resolution, etc. Similar functionality to neofetch 
	//		command on Linux
	//	@param: None
	//	@returns: int value to indicate either success or failure
	int NeoFetch();
};

