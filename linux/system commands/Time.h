// Author: Prajas Naik
// This file declares the Time class

#pragma once
#include <string>

using namespace std;

// This class models basic time related functions
class Time
{
    public:
        // public static method function: ConvertSecondsToHoursMinutesSeconds
        //      This function takes integer input of the number of seconds
        //      and converts the time to days, months, hours and seconds
        //  @param: seconds-Number of seconds
        //  @returns: A string containing the time in terms of days, hours, 
        //            minutes, seconds.
        static string ConvertSecondsToDaysHoursMinutesSeconds(int seconds);
};
