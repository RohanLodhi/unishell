// Author: Prajas Naik
// This file contains the HelperFunctions class

#pragma once

// Built-in header files
#include <string>
#include <windows.h>
#include <comdef.h>

using namespace std;

// HelperFunctions Class contains any additional functionalities. 
// TODO: check whether this class is needed or whether this code
// can be implemented elsewhere
class HelperFunctions
{
public:
	// static public method function: ConvertBstrToString
	//		Converts the BSTR input to the std::string data 
	//	@param: BSTR input - The BSTR data we want to convert
	//	@returns: std::string - The converted string of the input
	//	is returned
	static string ConvertBstrToString(BSTR input);
};

