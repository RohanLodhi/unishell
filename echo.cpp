#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class EchoCommand {
public:
    static void execute(const std::string& input) {
        bool appendNewline = true;
        bool interpretBackslashes = false;

        std::istringstream iss(input);
        std::string arg;
        while (iss >> arg) {
            if (arg == "-n") {
                appendNewline = false;
                continue;
            } else if (arg == "-e") {
                interpretBackslashes = true;
                continue;
            } else if (arg == "-E") {
                interpretBackslashes = false;
                continue;
            }

            // Output the argument, interpreting backslashes if necessary
            if (interpretBackslashes) {
                printWithEscapes(arg);
            } else {
                std::cout << arg << " ";
            }
        }

        if (appendNewline) {
            std::cout << std::endl;
        }
    }

private:
    static void printWithEscapes(const std::string& str) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\\' && i + 1 < str.length()) {
                if (str[i + 1] == 'e' || str[i + 1] == 'E') {
                    // ANSI escape sequence start
                    std::cout << "\033";
                    i++; // Skip 'e' or 'E'
                } else {
                    // Handle other escape sequences
                    switch (str[i + 1]) {
                        case 'a': std::cout << '\a'; break; // Alert (bell)
                        case 'b': std::cout << '\b'; break; // Backspace
                        case 'f': std::cout << '\f'; break; // Form feed
                        case 'n': std::cout << '\n'; break; // New line
                        case 'r': std::cout << '\r'; break; // Carriage return
                        case 't': std::cout << '\t'; break; // Horizontal tab
                        case 'v': std::cout << '\v'; break; // Vertical tab
                        case '\\': std::cout << '\\'; break; // Backslash
                        default: std::cout << str[i + 1]; // Unknown escape sequence
                    }
                    i++; // Skip the next character
                }
            } else {
                std::cout << str[i];
            }
        }
        std::cout << " ";
    }


};

int main() {
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        if (input.find("echo") == 0) {
            EchoCommand::execute(input.substr(5));
        } else {
            std::cout << "Command not recognized." << std::endl;
        }
    }

    return 0;
}
