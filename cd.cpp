#include <iostream>
#include <unistd.h>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // Get the directory from the user
    std::cout << "Enter the desired directory path: ";
    std::string desiredDirectory;
    std::getline(std::cin, desiredDirectory);

    if (chdir(desiredDirectory.c_str()) == 0) {
        // Successfully changed the current directory
        std::cout << "Current directory changed to: " << desiredDirectory << std::endl;
    } else {
        perror("chdir() error");
        return 1;
    }

    return 0;
}