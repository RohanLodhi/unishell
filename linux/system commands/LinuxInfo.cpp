// Author: Prajas Naik
// This file implements the LinuxInfo class

#include "LinuxInfo.h"

using namespace std;


// public constructor
LinuxInfo :: LinuxInfo() : mUptime(""), mOsName(""), mKernelVersion("") 
{
    FindKernelVersion();
    FindOsName();
}


//public accessor functions
string LinuxInfo::GetKernelVersion() const
{
    return mKernelVersion;
}

string LinuxInfo::GetOsName() const
{
    return mOsName;
}

string LinuxInfo::GetUptime()
{
    CalculateUptime();
    return mUptime;
}

// private method function: CalculateUptime 
//      This function fetches the information about
//      the amount of time the system has been turned
//      on from the appropriate directory
//  @param: None
//  @returns: An integer indicating whether the operation succeeded or not. 
int LinuxInfo::CalculateUptime()
{
    const char *path = "/proc/uptime";
    int upTime = 0;
    ifstream upTimeFile(path);
    if (!upTimeFile.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return EXIT_FAILURE;
    }
    string line;
    try 
    {
        getline(upTimeFile, line); 
        size_t token = line.find(" ");
        upTime = stoi(line.substr(0, token + 1));
        mUptime = Time::ConvertSecondsToDaysHoursMinutesSeconds(upTime);
    
    }
    catch (...)
    {
        cerr << "Could not find uptime information" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;    

}


// private method function: FindOsName 
//      This function fetches the information about
//      the OS name using the uname function.
//  @param: None
//  @returns: An integer indicating whether the operation succeeded or not. 
int LinuxInfo::FindOsName()
{
    struct utsname buf;
    try
    {
        uname(&buf);
        string OS = buf.version;
        size_t splitter = OS.find(" ");
        string osName = OS.substr(0, splitter);
        splitter = osName.find("~");
        mOsName = osName.substr(splitter + 1) + " " + buf.machine;    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    
    return EXIT_SUCCESS;
}

// private method function: FindKernelVersion 
//      This function fetches the information about
//      the Kernel Version using the uname function.
//  @param: None
//  @returns: An integer indicating whether the operation succeeded or not. 
int LinuxInfo::FindKernelVersion()
{
    struct utsname buf;
    try
    {
        uname(&buf);
        mKernelVersion = buf.release;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    
    return EXIT_SUCCESS;
}
