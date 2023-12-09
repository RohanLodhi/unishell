#include <iostream>
#include <unordered_map>
#include <cctype>
#include <sstream>

std::string toUpperCase(const std::string& input) {
    std::string result = input;
    for (char& c : result) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return result;
}

void displayManual(const std::string& command) {
    // map for command descriptions
    std::unordered_map<std::string, std::string> commandDescriptions = {
        {"MKDIR", "This command is used to create a new directory."},
        {"CAT", "This command is used to display the contents of a file."},
        {"RM", "This command is used to remove files or directories."},
        {"CP", "This command is used to copy files or directories."},
        {"MV", "This command is used to move or rename files or directories."},
        {"GREP", "This command is used to search for a specific pattern within files."},
        {"TOUCH", "This command is used to create a new empty file."},
        {"RMDIR", "This command is used to remove an empty directory."},
        {"LS", "This command is used to list the contents of a directory."},
        {"CD", "This command is used to change the current directory."},
        {"PWD", "This command is used to print the path of the current working directory."},
        {"NEOFETCH", "This command is used to display system information alongside the ASCII distribution logo."},
        {"WHOAMI", "This command is used to print the username of the current user."},
        {"IFCONFIG", "This command is used to display or configure network interfaces."},
        {"ECHO", "This command is used to display a line of text."},
        {"MAN", "This command is used to display the full Manual."}
    };

    // Find the command in the map and print its description
    if (command == "MAN") {
        for (const auto& pair : commandDescriptions) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    } else {
        // Find the command in the map and print its description
        auto it = commandDescriptions.find(command);
        if (it != commandDescriptions.end()) {
            std::cout << it->first << ": " << it->second << std::endl;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}

void MAN(const std::vector<std::string>& tokens) {
    // If there's a second word, display the manual for the second word
    // Otherwise, display the manual for all commands
    if (tokens.size() > 1) {
        displayManual(tokens[1]);
    } else {
        displayManual("MAN");
    }
}

// Just to Check the working
//int main() {
//    std::string command;
//    std::cout << "Enter a command: ";
//    getline(std::cin, command); // Use getline to read the entire line
//    command = toUpperCase(command);
//
//    // Split the command into words
//    std::istringstream iss(command);
//    std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
//
//    // If the first word is "MAN" and there's a second word, display the manual for the second word
//    // Otherwise, display the manual for the first word
//    if (words[0] == "MAN" && words.size() > 1) {
//        MAN(words[1]);
//    } else {
//        MAN(words[0]);
//    }

//    return 0;
//}
