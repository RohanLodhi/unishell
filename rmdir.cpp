#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem; // namespace alias

// check if a directory exists at the given path
bool directory_exists(const std::string& path) {
    return fs::exists(path) && fs::is_directory(path);
}

// remove directory and its contents
void removing_directory(const std::string& directoryPath) {
    try {
        // if directory exists, then remove 
        if (directory_exists(directoryPath)) {
            fs::remove_all(directoryPath);
            std::cout << "Directory removed successfully." << std::endl;
        } else {
            std::cerr << "Error: Directory does not exist." << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error removing directory: " << e.what() << std::endl;
    }
}

int main() {
    std::string directoryPath; 
    std::cout << "Enter directory path to remove: ";
    std::cin >> directoryPath;

    removing_directory(directoryPath);

    return 0;
}
