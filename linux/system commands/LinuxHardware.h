#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class LinuxHardware
{
    private:
        string mCpuName;
        vector<string> mGpuNames;
        int mTotalMemory;
        int mUtilizedMemory;
        string mMemory;
        string mDisplayResolution;

        int FindGpuNames();
        int FindCpuName();
        int FindDisplayResolution();
        int FindAvailableMemory();

    public:
        LinuxHardware();
        vector<string> GetGpuNames() const;
        string GetCpuName() const;
        string GetMemoryUtilization();
        string GetDisplayResolution() const;
};