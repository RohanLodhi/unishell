#pragma once
#include<iostream>
#include "LinuxHardware.h"
#include "LinuxInfo.h"
#include <unistd.h>
#include <limits.h>

using namespace std;

class LinuxSystem
{
    private:    
        LinuxHardware mDevice;
        LinuxInfo mLinux;
        string mUserName;
        string mHostName;   
        string mModel;
        const string mShell = "unibash 1.0";

        int FindModelName();
        int FindUserName();
        int FindHostName();
    public:
        LinuxSystem();
        int Neofetch();
        int WhoAmI();
};