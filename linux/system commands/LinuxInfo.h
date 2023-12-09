#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sys/utsname.h>

#include "Time.h"

using namespace std;

class LinuxInfo
{
    private:
        string mOsName;
        string mKernelVersion;
        string mUptime;
        int CalculateUptime();
        int FindOsName();
        int FindKernelVersion();
    public:
        LinuxInfo();
        string GetKernelVersion() const;
        string GetOsName() const;
        string GetUptime();
};