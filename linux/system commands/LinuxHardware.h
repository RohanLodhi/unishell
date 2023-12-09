// Author: Prajas Naik
// This file declares the LinuxHardware class

#pragma once

// Builr-in header files
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// The LinuxHardware class contains the linux implementation 
// of obtaining hardware information about the system. It models
// the linux hardware information
class LinuxHardware
{
    private:
        //private data members
        vector<string> mGpuNames;
        string mCpuName;
        string mMemory;
        string mDisplayResolution;
        int mTotalMemory;
        int mUtilizedMemory;

        // private method function: FindGpuNames
        //      This function obtains the GPU names by using
        //      an in-built command to get all possible GPUs
        //      and then cleaning the names and storing it in the
        //      mGpuNames vector.
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not
        int FindGpuNames();

        // private method function: FindCpuName
        //      This function obtains the CPU name by 
        //      searching the appropriate file in the /proc directory
        //      and storing the information in the mCpuNames data member
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not
        int FindCpuName();

        // private method function: FindDisplayResolution
        //      This function obtains the display resolution by 
        //      searching the appropriate file in the /sys directory
        //      and storing the information in the mDisplayResolution data member
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not
        int FindDisplayResolution();

        // private method function: FindAvailableMemory
        //      This function obtains the memory usageby 
        //      searching the appropriate file in the /proc directory
        //      and storing the information in the mMemory data member
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not
        int FindAvailableMemory();

    public:
        // public constructor
        LinuxHardware();

        //public accessor functions
        vector<string> GetGpuNames() const;
        string GetCpuName() const;
        string GetMemoryUtilization();
        string GetDisplayResolution() const;
};