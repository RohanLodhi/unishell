// Author: Prajas Naik
// This file contains the declaration of the LinuxSystem class

#pragma once

// Built-in header files
#include <iostream>
#include <unistd.h>
#include <limits.h>

// User-defined header files
#include "LinuxHardware.h"
#include "System.h"
#include "LinuxInfo.h"

using namespace std;

// The Linux System Class models the device that the program is 
// running on, including the OS, the Hardware, and the system 
// information
class LinuxSystem : public System
{
    private:  
        // User-defined private data members  
        LinuxHardware mDevice;
        LinuxInfo mLinux;

        // Built in private data members
        string mUserName;
        string mHostName;   
        string mModel;
        const string mShell = "unibash 1.0";

        // private method function: FindModelName 
        //      This function fetches the information about
        //      the model name using the appropriate directory.
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not. 
        int FindModelName();

        // private method function: FindUserName 
        //      This function fetches the information about
        //      the username using the getlogin_r function.
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not. 
        int FindUserName();

        // private method function: FindHostName 
        //      This function fetches the information about
        //      the host name using the gethostname function.
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not. 
        int FindHostName();
    public:

        // public constructor
        LinuxSystem();

        // public method function: Neofetch
        //      This function prints the system information along with the ascii
        //      symbol of the Operating System used by the system
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not.
        int Neofetch();

        // public method function: Neofetch
        //      This function prints the username of the current user
        //  @param: None
        //  @returns: An integer indicating whether the operation succeeded or not.
        int WhoAmI();
};
