#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "./../../Network.h"

using namespace std;

class NetworkCommands : public Network {
private:
    map<string, vector<string>> interfaceIPs;

    void processInterfaceInfo(const string& line) {
        istringstream iss(line);
        string interfaceName, data;
        iss >> interfaceName >> data;

        if (!interfaceName.empty() && interfaceName.back() == ':') {
            interfaceName.pop_back(); // Remove the colon

            // Initialize an entry for the interface in the map
            interfaceIPs[interfaceName] = {};
        }
    }

    void processRoutingInfo(const string& line) {
        // Find the position of "|--"
        string::size_type pos = line.find("|--");

        // Check if "|--" is present in the line
        if (pos != string::npos) {
            // Extract the substring after "|--"
            string substring = line.substr(pos + 3);

            // Use stringstream to extract each token
            istringstream iss(substring);
            string token;

            // Iterate through tokens and print only valid IPv4 addresses
            while (iss >> token) {
                if (token.find('.') != string::npos && token != "0.0.0.0" && !token.compare(0, 3, "127")) {
                    // Store the IPv4 address in the map under the current interface
                    if (!interfaceIPs.empty()) {
                        interfaceIPs.rbegin()->second.push_back(token);
                    }
                }
            }
        }
    }

public:
    void ifconfigCommand() {
        // Read network interface information from /proc/net/dev
        ifstream devFile("/proc/net/dev");
        if (!devFile.is_open()) {
            cerr << "Error opening /proc/net/dev file." << endl;
            return;
        }

        // Skip the header lines
        string line;
        for (int i = 0; i < 2; ++i) {
            getline(devFile, line);
        }

        // Process the rest of the lines
        while (getline(devFile, line)) {
            processInterfaceInfo(line);
        }

        // Read routing information from /proc/net/fib_trie
        ifstream fibTrieFile("/proc/net/fib_trie");
        if (!fibTrieFile.is_open()) {
            cerr << "Error opening /proc/net/fib_trie file." << endl;
            return;
        }

        // Process the lines
        while (getline(fibTrieFile, line)) {
            processRoutingInfo(line);
        }

        // Print the collected IPv4 addresses for each interface
        for (const auto& [interface, ips] : interfaceIPs) {
            for (const auto& ip : ips) {
                cout << "Interface: " << interface << "\tIPv4 Address: " << ip << endl;
            }
        }
    }
};

// int main() {
//     NetworkCommands networkCommands;
//     networkCommands.ifconfigCommandLinux();

//     return 0;
// }