#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#ifdef _WIN32
    #include <direct.h> // windows specific
    #include "windows/system commands/WindowsSystem.h" //windows specific
    #include "networkCommandsWindows.cpp" // windows specific
#endif // _WIN32

#ifdef __linux__ 
//Add linux specific header files
#endif // __linux__ 


#include "fileCommands.cpp"
#include "echo.cpp"
#include "DirectoryCommands.cpp"
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
    //home directory of linux needs to be put
    char cwd[1024];
    string path = "/";
    if (_getcwd(cwd, sizeof(cwd)) != NULL)
        path = cwd;
    // WindowsSystem windowsSystem = WindowsSystem();
    // NetworkCommands network = NetworkCommands();
    FileManager manager = FileManager();
    EchoCommand echohandler = EchoCommand();
    DirectoryCommands directories = DirectoryCommands();

    int status = 0;
    while (true) {
        cout << "Path: " << path << endl;
        string input;
        getline(cin, input);
        vector<string> tokens = parseInput(input);
        
        switch (hashit(tokens[0])) {
        case MKDIR:
            directories.mkdir(tokens[1]);
            break;
        case CAT:
            if (tokens.size() == 2)
            {
                manager.catFile(tokens[1]);
            }
            else
            {
                cerr << "Wrong command" << endl;
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
                cerr << "Wrong command" << endl;
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
                cerr << "Wrong command" << endl;
            }

            // cp
            break;
        case MV:
            if (tokens.size() == 3)
            {
                manager.moveOrCopyFile(tokens[1], tokens[2], false);
            }
            else
            {
                cerr << "Wrong command" << endl;
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
                cerr << "Wrong command" << endl;
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
                cerr << "Wrong command" << endl;
            }

            // touch
            break;
        case RMDIR:
            directories.rmdir(tokens[1]);
            break;
        case LS:
            if (tokens.size() == 1) {
                directories.ls();
            }
            else {
                directories.ls(tokens[1]);
            }
            break;
        case CD:
            directories.cd(tokens[1]);
            break;
        case PWD:
            directories.pwd();
            break;
        case NEOFETCH:
            windowsSystem.NeoFetch();
            // neofetch
            break;
        case WHOAMI:
            windowsSystem.WhoAmI();
            // whoami
            break;
        case IFCONFIG:
            network.ifconfigCommand();
            // ifconfig
            break;
        case ECHO:
            echohandler.execute(input.substr(5));
            break;
        default:
            status = system(input.c_str());
            if(status != 0)
                cout << "Unknown command" << endl;
            break;
        }

    }
    return 0;
}
