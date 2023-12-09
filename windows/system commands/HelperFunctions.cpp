// Author: Prajas Naik
// This file implements the HelperFunctions class
#include "HelperFunctions.h"

// static public method function: ConvertBstrToString
//		Converts the BSTR input to the std::string data 
//	@param: BSTR input - The BSTR data we want to convert
//	@returns: std::string - The converted string of the input
//	is returned
string HelperFunctions::ConvertBstrToString(BSTR input)
{
	_bstr_t bstr_t(input);
	const char* char_ptr = bstr_t;
	return string(char_ptr ? char_ptr : "");
}