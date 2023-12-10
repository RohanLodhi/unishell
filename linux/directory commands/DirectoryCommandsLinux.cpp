#include <iostream>
#include <filesystem>
#include <unistd.h> // For getcwd on Linux
#include <sys/stat.h> // For mkdir on Linux
#include <string>

namespace fs = std::filesystem;

class DirectoryCommands {
public:
    bool cd(const std::string& desiredDirectory) {
        try {
            // Attempt to change the current directory
            fs::current_path(desiredDirectory);
            return true;  // Directory change successful
        } catch (const std::exception& e) {
            return false;  // Directory change unsuccessful
        }
    }
    
    void pwd() {
        // Linux-specific implementation uses getcwd
        char tmp[256];
        if (getcwd(tmp, sizeof(tmp)) != nullptr) {
            std::cout << "Current working directory: " << tmp << std::endl;
        } else {
            std::cerr << "Error getting current working directory." << std::endl;
        }
    }

    void mkdir(const std::string& directory_name) {
        if (::mkdir(directory_name.c_str(), 0777) != 0) {
            std::cerr << "Error creating directory: " << strerror(errno) << std::endl;
        }
    }

    // Other methods remain unchanged

private:
    fs::path currentPath() {
        // Linux implementation remains the same
    }
};
