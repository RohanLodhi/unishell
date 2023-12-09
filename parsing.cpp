#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

enum Command {
    MKDIR,
    CAT,
    RM,
    CP,
    MV,
    GREP,
    TOUCH,
    RMDIR,
    LS,
    CD,
    PWD,
    NEOFETCH,
    WHOAMI,
    IFCONFIG,
    UNKNOWN
    //place commands here
};

Command hashit (string const& inString) {
    if (inString == "mkdir") return MKDIR;
    if (inString == "cat") return CAT;
    if (inString == "rm") return RM;
    if (inString == "cp") return CP;
    if (inString == "mv") return MV;
    if (inString == "grep") return GREP;
    if (inString == "touch") return TOUCH;
    if (inString == "rmdir") return RMDIR;
    if (inString == "ls") return LS;
    if (inString == "cd") return CD;
    if (inString == "pwd") return PWD;
    if (inString == "neofetch") return NEOFETCH;
    if (inString == "whoami") return WHOAMI;
    if (inString == "ifconfig") return IFCONFIG;
    return UNKNOWN;
}

vector<string> parseInput(const string& input) {
    vector<string> tokens;
    istringstream stream(input);
    string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}





int main() {
    //home directory of linux needs to be put
    string path = "/home/mukund";
    while(true) {
        cout << "Path: " << path << endl;
        string input;
        getline(cin, input);
        vector<string> tokens = parseInput(input);

        switch(hashit(tokens[0])) {
            case MKDIR:
                cout << "mkdir command" << endl;
// mkdir
                break;
            case CAT:
                cout << "cat command" << endl;
// cat
                break;
            case RM:
                cout << "rm command" << endl;
// rm
                break;
            case CP:
                cout << "cp command" << endl;
// cp
                break;
            case MV:
                cout << "mv command" << endl;
// mv
                break;
            case GREP:
                cout << "grep command" << endl;
// grep
                break;
            case TOUCH:
                cout << "touch command" << endl;
// touch
                break;
            case RMDIR:
                cout << "rmdir command" << endl;
// rmdir
                break;
            case LS:
                cout << "ls command" << endl;
// ls
                break;
            case CD:
                cout << "cd command" << endl;
// cd
                break;
            case PWD:
                cout << "pwd command" << endl;
// pwd
                break;
            case NEOFETCH:
                cout << "neofetch command" << endl;
// neofetch
                break;
            case WHOAMI:
                cout << "whoami command" << endl;
// whoami
                break;
            case IFCONFIG:
                cout << "ifconfig command" << endl;
// ifconfig
                break;
//default unknown command rakha hai
            default:
                cout << "Unknown command" << endl;
                break;
        }

    }
    return 0;
}
