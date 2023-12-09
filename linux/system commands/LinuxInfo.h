//Author: Prajas Naik
// This file contains the declaration of the LinuxInfo class

#pragma once

// Built-in Header files
#include <iostream>
#include <string>
#include <fstream>
#include <sys/utsname.h>

// USer-defined Header Files
#include "Time.h"

using namespace std;

// The LinuxInfo class captures the information about the 
// Linux Operating System the program is running on
//
class LinuxInfo
{
    private:
        // Private data members
        string mOsName;
        string mKernelVersion;
        string mUptime;

        // private method function: CalculateUptime 
        //      This function fetches the information about
        //      the amount of time the system has been turned
        //      on from the appropriate directory
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not. 
        int CalculateUptime();

        // private method function: FindOsName 
        //      This function fetches the information about
        //      the OS name using the uname function.
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not. 
        int FindOsName();

        // private method function: FindKernelVersion 
        //      This function fetches the information about
        //      the Kernel Version using the uname function.
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not. 
        int FindKernelVersion();
    public:

        // public constructor
        LinuxInfo();

        // public accessor functions
        string GetKernelVersion() const;
        string GetOsName() const;
        string GetUptime();
};