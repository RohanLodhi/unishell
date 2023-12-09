// Author: Prajas Naik
// This file implements the Time class.


#include "Time.h"

using namespace std;


// public method function: ConvertStringToTm
//		This functions takes in an input string with the time in
//		seconds and converts it to an object of the type tm given
//		by the tm struct. It is a static function
//	@param: string with time in seconds
//	@returns: an object with datatype of tm
tm Time::ConvertStringToTm(string timeString)
{
	tm time = {};
	istringstream stringStream(timeString);
    stringStream >> get_time(&time, "%Y%m%d%H%M%S"); // read date and time
    stringStream.ignore(); // skip decimal point
    stringStream.ignore(6); // skip microseconds
    stringStream.ignore(); // skip timezone sign
    stringStream.ignore(3); // skip timezone
    if (stringStream.fail())
        std::cout << "Parse failed\n";
    else 
        return time;
}

// public method function: CalculateDifference
//		This function calculates the difference in time in seconds
//		between two objects of datatype tm
//	@param: pCurrentTime - a pointer to an object of datatype tm
//			that tells the current time
//	@param: pBootUpTime - a pointer to an object of datatype tm
//			that tells the time of last boot up of the device
//	@returns: The difference in seconds between the input times
double Time::CalculateDifference(tm *pCurrentTime, tm *pBootUpTime)
{
    time_t time1 = std::mktime(pCurrentTime);
    time_t time2 = std::mktime(pBootUpTime);
    return difftime(time1, time2);
}

// public method function: SecondsToDaysHoursMinutesSeconds
//		This function takes the amount of time in seconds and returns
//		a string with the same time represented in terms of days,
//		minutes and seconds
//	@param: seconds - The number of seconds given as input
//	@returns: A string with the input time written in terms of
//			  number of days, hours, minutes and seconds
string Time::SecondsToDaysHoursMinutesSeconds(double seconds)
{
    
    int days = (int)seconds / 86400;
    seconds -= days * 86400;
    int hours = (int)seconds / 3600;
    seconds -= hours * 3600;
    int minutes = seconds / 60;
    seconds -= minutes * 60;
    
    stringstream stringStream;
    stringStream << fixed << setprecision(2) << seconds; //setting precision of the number of seconds to 2 decimal places
    string secondsString = stringStream.str();

    if (days > 0)
    {
        return to_string(days) + " days " + to_string(hours) + " hours " + to_string(minutes) + " minutes " + secondsString + " seconds";
    }
    else if (hours > 0)
    {
        return to_string(hours) + " hours " + to_string(minutes) + " minutes " + secondsString + " seconds";
    }
    else if (minutes > 0)
    {
        return to_string(minutes) + " minutes " + secondsString + " seconds";
    }
    else
        return secondsString + " seconds";
     
}
