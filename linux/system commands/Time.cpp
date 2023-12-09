#include "Time.h"

string Time::ConvertSecondsToHoursMinutesSeconds(int seconds)
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