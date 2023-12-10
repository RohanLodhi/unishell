#include <iostream>
#include <filesystem>
#include <direct.h>
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
        // Windows implementation uses _getcwd
        char tmp[256];
        if (_getcwd(tmp, sizeof(tmp)) != nullptr) {
            std::cout << "Current working directory: " << tmp << std::endl;
        } else {
            std::cerr << "Error getting current working directory." << std::endl;
        }
    }

    void mkdir(const std::string& directory_name) {
        // Windows-specific mkdir with _mkdir
        if (_mkdir(directory_name.c_str()) != 0) {
            std::cerr << "Error creating directory: " << strerror(errno) << std::endl;
        }
    }

    bool directoryExists(const std::string& path) {
        return fs::exists(path) && fs::is_directory(path);
    }

    void rmdir(const std::string& directoryPath) {
        try {
            // If directory exists, then remove
            if (directoryExists(directoryPath)) {
                fs::remove_all(directoryPath);
                std::cout << "Directory removed successfully." << std::endl;
            } else {
                std::cerr << "Error: Directory does not exist." << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error removing directory: " << e.what() << std::endl;
        }
    }

    void ls(const std::string& path = ".") {
        try {
            for (const auto& entry : fs::directory_iterator(path)) {
                std::cout << entry.path().filename() << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error listing directory: " << e.what() << std::endl;
        }
    }

private:
    std::filesystem::path currentPath() {
        return std::filesystem::current_path();
    }
};
