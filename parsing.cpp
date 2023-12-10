#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <direct.h> // windows specific
#include "windows/system commands/WindowsSystem.h" //windows specific
#include "windows/network commands/networkCommandsWindows.cpp" // windows specific
#include "windows/directory commands/DirectoryCommandsWindows.cpp"
#define OS 0
#endif // _WIN32

#ifdef __linux__ 
#include <unistd.h>
#include "linux/system commands/LinuxSystem"
#include "linux/network commands/networkCommandsLinux.cpp"
#include "linux/directory commands/DirectoryCommandsLinux.cpp"
#define OS 1
#endif // __linux__ 


#include "fileCommands.cpp"
#include "echo.cpp"

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
    ECHO,
    UNKNOWN
    //place commands here
};

Command hashit(string const& inString) {
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
    if (inString == "echo") return ECHO;
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
    System* pSystemObject = nullptr;
    Network* pNetworkObject = nullptr;
    Directories* pDirectoriesObject = nullptr;
#ifdef _WIN32
    pSystemObject = new WindowsSystem();
    pNetworkObject = new NetworkCommands();
    pDirectoriesObject = new DirectoryCommands();
#endif
#ifdef __linux__
    pSystemObject = new LinuxSystem();
    pNetworkObject = new NetworkCommands();
    pDirectoriesObject = new DirectoryCommands();
#endif
    FileManager manager = FileManager();
    EchoCommand echohandler = EchoCommand();
    string path = pDirectoriesObject->getPath();

    int status = 0;
    while (true) {
        cout << path << ">> ";
        string input;
        getline(cin, input);
        vector<string> tokens = parseInput(input);

        switch (hashit(tokens[0])) {
        case MKDIR:
            pDirectoriesObject->mkdir(tokens[1]);
            break;
        case CAT:
            if (tokens.size() == 2)
            {
                manager.catFile(tokens[1]);
            }
            else
            {
                cerr << "Incorrect number of arguments for cat. Expected 1." << endl;
            }

            // cat
            break;
        case RM:
            if (tokens.size() == 2)
            {
                manager.removeFile(tokens[1]);
            }
            else
            {
                cerr << "Incorrect number of arguments for rm. Expected 1." << endl;
            }

            // rm
            break;
        case CP:
            if (tokens.size() == 3)
            {
                manager.moveOrCopyFile(tokens[1], tokens[2], false);
            }
            else
            {
                cerr << "Incorrect number of arguments for cp. Expected 2." << endl;
            }

            // cp
            break;
        case MV:
            if (tokens.size() == 3)
            {
                manager.moveOrCopyFile(tokens[1], tokens[2], true);
            }
            else
            {
                cerr << "Incorrect number of arguments for mv. Expected 2." << endl;
            }
            // mv
            break;
        case GREP:
            if (tokens.size() == 3)
            {
                manager.grepFile(tokens[1], tokens[2]);
            }
            else
            {
                cerr << "Incorrect number of arguments for grep. Expected 2." << endl;
            }

            // grep
            break;
        case TOUCH:
            if (tokens.size() == 2)
            {
                manager.touchFile(tokens[1]);
            }
            else
            {
                cerr << "Incorrect number of arguments for grep. Expected 1." << endl;
            }

            // touch
            break;
        case RMDIR:
            pDirectoriesObject->rmdir(tokens[1]);
            path = pDirectoriesObject->getPath();
            break;
        case LS:
            if (tokens.size() == 1) {
                pDirectoriesObject->ls();
            }
            else {
                pDirectoriesObject->ls(tokens[1]);
            }
            break;
        case CD:
            pDirectoriesObject->cd(tokens[1]);
            path = pDirectoriesObject->getPath();
            break;
        case PWD:
            pDirectoriesObject->pwd();
            break;
        case NEOFETCH:
            pSystemObject->NeoFetch();
            // neofetch
            break;
        case WHOAMI:
            pSystemObject->WhoAmI();
            // whoami
            break;
        case IFCONFIG:
            pNetworkObject->ifconfigCommand();
            // ifconfig
            break;
        case ECHO:
            echohandler.execute(input);
            break;
        default:
            status = system(input.c_str());
            if (status != 0)
                cout << "Unknown command" << endl;
            break;
        }

    }
    return 0;
}
