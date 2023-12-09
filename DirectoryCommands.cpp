#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <string>
#if defined(_WIN32)
#include <direct.h>  // For windows
#define mkdir_function _mkdir
#else
#include <sys/stat.h> // For linux or macOS
#define mkdir_function mkdir
#endif

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
        char tmp[256];  // Temp array to store the current working directory

        // Get the current working directory
        if (getcwd(tmp, sizeof(tmp)) != nullptr) {
            std::cout << "Current working directory: " << tmp << std::endl;
        } else {
            std::cerr << "Error getting current working directory." << std::endl;
        }
    }

    void mkdir(const std::string& directory_name) {
        // Check if the path is incomplete (relative) or complete (absolute)
        std::filesystem::path full_path = (fs::path(directory_name).is_absolute()) ? directory_name : currentPath() / directory_name;

        // Attempt to create the directory
        try {
            fs::create_directory(full_path);
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error creating directory: " << e.what() << std::endl;
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