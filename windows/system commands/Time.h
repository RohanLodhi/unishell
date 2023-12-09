// Author: Prajas Naik
// This file contains the declaration for the Time Class


#pragma once

//Built-in header files
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <chrono>

using namespace std;

/// 
/// The Time class is a class that organizes all the functions
/// required to manage time in the project. All the functions
/// in this class are static and do not need to be called from
/// a specific object
///
class Time
{
public:
	// public method function: ConvertStringToTm
	//		This functions takes in an input string with the time in
	//		seconds and converts it to an object of the type tm given
	//		by the tm struct. It is a static function
	//	@param: string with time in seconds
	//	@returns: an object with datatype of tm
	static tm ConvertStringToTm(string timeString);

	// public method function: CalculateDifference
	//		This function calculates the difference in time in seconds
	//		between two objects of datatype tm
	//	@param: pCurrentTime - a pointer to an object of datatype tm
	//			that tells the current time
	//	@param: pBootUpTime - a pointer to an object of datatype tm
	//			that tells the time of last boot up of the device
	//	@returns: The difference in seconds between the input times
	static double CalculateDifference(tm* pCurrentTime, tm* pBootUpTime);

	// public method function: SecondsToDaysHoursMinutesSeconds
	//		This function takes the amount of time in seconds and returns
	//		a string with the same time represented in terms of days,
	//		minutes and seconds
	//	@param: seconds - The number of seconds given as input
	//	@returns: A string with the input time written in terms of
	//			  number of days, hours, minutes and seconds
	static string SecondsToDaysHoursMinutesSeconds(double seconds);
};

