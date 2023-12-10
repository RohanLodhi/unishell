#include <iostream>
#include <windows.h>
#include <iphlpapi.h>

#include "Network.h"

#pragma comment(lib, "IPHLPAPI.lib")

class NetworkCommands : public Network {
public:
    void ifconfigCommand() {
        PIP_ADAPTER_INFO adapterInfo = new IP_ADAPTER_INFO();
        ULONG bufferSize = sizeof(IP_ADAPTER_INFO);

        if (GetAdaptersInfo(adapterInfo, &bufferSize) == ERROR_BUFFER_OVERFLOW) {
            delete[] adapterInfo;
            adapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(new char[bufferSize]);
        }

        if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {
            // Iterate through the adapters
            PIP_ADAPTER_INFO adapter = adapterInfo;
            while (adapter) {
                std::cout << "Adapter Name: " << adapter->AdapterName << std::endl;
                std::cout << "IP Address: " << adapter->IpAddressList.IpAddress.String << std::endl;
                std::cout << "Subnet Mask: " << adapter->IpAddressList.IpMask.String << std::endl;
                std::cout << "------------------------" << std::endl;

                adapter = adapter->Next;
            }
        }
        else {
            std::cerr << "Error getting adapter information." << std::endl;
        }

        // Clean up
        delete[] adapterInfo;
    }

private:
    // Add any additional private member functions or variables here if needed.
};
//
//int main() {
//    NetworkCommands networkCommands;
//    networkCommands.ifconfigCommand();
//
//    return 0;
//}
