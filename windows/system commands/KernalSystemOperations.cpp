// Author: Prajas Naik
// KernalSystemOperations.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "WindowsSystem.h"

using namespace std;

int main()
{   
    WindowsSystem system = WindowsSystem();
    system.NeoFetch();
    system.WhoAmI();
    return 0;
}

