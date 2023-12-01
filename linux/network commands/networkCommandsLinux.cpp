#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

class NetworkCommands {
private:
    std::map<std::string, std::vector<std::string>> interfaceIPs;

    void processInterfaceInfo(const std::string& line) {
        std::istringstream iss(line);
        std::string interfaceName, data;
        iss >> interfaceName >> data;

        if (!interfaceName.empty() && interfaceName.back() == ':') {
            interfaceName.pop_back(); // Remove the trailing colon

            // Initialize an entry for the interface in the map
            interfaceIPs[interfaceName] = {};
        }
    }

    void processRoutingInfo(const std::string& line) {
        // Find the position of "|--"
        std::string::size_type pos = line.find("|--");

        // Check if "|--" is present in the line
        if (pos != std::string::npos) {
            // Extract the substring after "|--"
            std::string substring = line.substr(pos + 3);

            // Use stringstream to extract each token
            std::istringstream iss(substring);
            std::string token;

            // Iterate through tokens and print only valid IPv4 addresses
            while (iss >> token) {
                if (token.find('.') != std::string::npos && token != "0.0.0.0" && !token.compare(0, 3, "127")) {
                    // Store the IPv4 address in the map under the current interface
                    if (!interfaceIPs.empty()) {
                        interfaceIPs.rbegin()->second.push_back(token);
                    }
                }
            }
        }
    }

public:
    void ifconfigCommandLinux() {
        // Read network interface information from /proc/net/dev
        std::ifstream devFile("/proc/net/dev");
        if (!devFile.is_open()) {
            std::cerr << "Error opening /proc/net/dev file." << std::endl;
            return;
        }

        // Skip the header lines
        std::string line;
        for (int i = 0; i < 2; ++i) {
            std::getline(devFile, line);
        }

        // Process the rest of the lines
        while (std::getline(devFile, line)) {
            processInterfaceInfo(line);
        }

        // Read routing information from /proc/net/fib_trie
        std::ifstream fibTrieFile("/proc/net/fib_trie");
        if (!fibTrieFile.is_open()) {
            std::cerr << "Error opening /proc/net/fib_trie file." << std::endl;
            return;
        }

        // Process the lines
        while (std::getline(fibTrieFile, line)) {
            processRoutingInfo(line);
        }

        // Print the collected IPv4 addresses for each interface
        for (const auto& [interface, ips] : interfaceIPs) {
            for (const auto& ip : ips) {
                std::cout << "Interface: " << interface << "\tIPv4 Address: " << ip << std::endl;
            }
        }
    }
};

int main() {
    NetworkCommands networkCommands;
    networkCommands.ifconfigCommandLinux();

    return 0;
}
