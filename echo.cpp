#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class EchoCommand {
    public:
        static void execute(const std::string& input) {
            if (input.size()==1){
                std::cout << "\n\n";
                return;
            }
            // Flags for arguments
            bool appendNewline = true;
            bool interpretBackslashes = false;

            // Tokenize the input string
            std::istringstream iss(input);
            std::string arg;
            while (iss >> arg) {
                // Check for command-line options -n, -e, -E
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

            // Add a newline character if -n option is not specified
            if (appendNewline) {
                std::cout << std::endl;
            }
        }

    private:
        // Prints a string with interpreted escape sequences
        static void printWithEscapes(const std::string& str) {
            for (size_t i = 0; i < str.length(); ++i) {
                if (str[i] == '\\' && i + 1 < str.length()) {
                    if (str[i + 1] == 'e' || str[i + 1] == 'E') {
                        // Handle ANSI escape sequence start
                        std::cout << "\033";
                        i++; // Skip 'e' or 'E'
                    } else {
                        // Handle other escape sequences
                        switch (str[i + 1]) {
                            // Output corresponding control characters
                            case 'a': std::cout << '\a'; break; // Alert 
                            case 'b': std::cout << '\b'; break; // Backspace
                            case 'f': std::cout << '\f'; break; // Form feed
                            case 'n': std::cout << '\n'; break; // New line
                            case 'r': std::cout << '\r'; break; // Carriage return
                            case 't': std::cout << '\t'; break; // Horizontal tab
                            case 'v': std::cout << '\v'; break; // Vertical tab
                            case '\\': std::cout << '\\'; break; // Backslash
                            default: std::cout << str[i + 1]; // Unknown escape sequence
                        }
                        i++; // skip the next character
                    }
                } else {
                    std::cout << str[i];
                }
            }
            std::cout << " ";
        }
};
