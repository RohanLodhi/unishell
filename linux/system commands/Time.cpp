// Author: Prajas Naik
// This file implements the Time class

#include "Time.h"


// public static method function: ConvertSecondsToHoursMinutesSeconds
//      This function takes integer input of the number of seconds
//      and converts the time to days, months, hours and seconds
//  @param: seconds-Number of seconds
//  @returns: A string containing the time in terms of days, hours, 
//            minutes, seconds.
string Time::ConvertSecondsToDaysHoursMinutesSeconds(int seconds)
{
    int hours = seconds / 3600;
    seconds -= hours * 3600;
    int minutes = seconds / 60;
    seconds -= minutes * 60;
    if (hours > 0)
        return to_string(hours) + " hours " + to_string(minutes) + " minutes " + to_string(seconds) + " seconds";
    else if (minutes > 0)
        return to_string(minutes) + " minutes " + to_string(seconds) + " seconds";
    else 
        return to_string(seconds) + " seconds";
}