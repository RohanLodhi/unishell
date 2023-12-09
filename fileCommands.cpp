#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

// Class representing a FileManager for file manipulation operations
class FileManager
{
public:
    // Method to remove a file
    // Parameters: const string &filename - the name of the file to be removed
    // Return type: bool - true if the file is successfully removed, false otherwise
    bool removeFile(const string &filename)
    {
        if (remove(filename.c_str()) == 0)
        {
            cout << "File '" << filename << "' successfully removed.\n";
            return true;
        }
        else
        {
            cerr << "Error removing file '" << filename << "'.\n";
            return false;
        }
    }

    // Method to display the contents of a file
    // Parameters: const string &filename - the name of the file to be displayed
    // Return type: void
    void catFile(const string &filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            cout << "Contents of file '" << filename << "':\n";
            cout << file.rdbuf() << endl;
            file.close();
        }
        else
        {
            cerr << "Error opening file '" << filename << "'.\n";
        }
    }

    // Method to create a new file
    // Parameters: const string &filename - the name of the file to be created
    // Return type: void
    void touchFile(const string &filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            cout << "File '" << filename << "' created.\n";
            file.close();
        }
        else
        {
            cerr << "Error creating file '" << filename << "'.\n";
        }
    }

    // Method to move or copy a file
    // Parameters: const string &source - the source file, const string &destination - the destination file,
    // bool isMove - true if it's a move operation, false if it's a copy operation
    // Return type: bool - true if the file is successfully moved or copied, false otherwise
    bool moveOrCopyFile(const string &source, const string &destination, bool isMove)
    {
        ifstream sourceFile(source, ios::binary);
        ofstream destFile(destination, ios::binary);

        if (sourceFile.is_open() && destFile.is_open())
        {
            destFile << sourceFile.rdbuf();
            sourceFile.close();
            destFile.close();

            cout << "File '" << source << "' successfully " << (isMove ? "moved" : "copied") << " to '" << destination << "'.\n";
            return true;
        }
        else
        {
            cerr << "Error " << (isMove ? "moving" : "copying") << " file from '" << source << "' to '" << destination << "'.\n";
            return false;
        }
    }

    // Method to search for a string in a file and display lines containing the string
    // Parameters: const string &filename - the name of the file to be searched, const string &searchString - the string to search for
    // Return type: void
    void grepFile(const string &filename, const string &searchString)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            cout << "Lines containing '" << searchString << "' in file '" << filename << "':\n";
            string line;
            while (getline(file, line))
            {
                if (line.find(searchString) != string::npos)
                {
                    cout << line << '\n';
                }
            }
            file.close();
        }
        else
        {
            cerr << "Error opening file '" << filename << "'.\n";
        }
    }
};

// Function to process user commands
// Parameters: const string &userInput - the user's input command, FileManager &fileManager - the FileManager object
// Return type: void
void processCommand(const string &userInput, FileManager &fileManager)
{
    size_t spacePos = userInput.find(' ');
    if (spacePos != string::npos && spacePos < userInput.size() - 1)
    {
        string command = userInput.substr(0, spacePos);
        string args = userInput.substr(spacePos + 1);

        if ((command == "mv" || command == "grep" || command == "cp") && args.find(' ') != string::npos)
        {
            size_t secondSpacePos = args.find(' ');
            string arg1 = args.substr(0, secondSpacePos);
            string arg2 = args.substr(secondSpacePos + 1);

            if (command == "mv" || command == "cp")
            {
                fileManager.moveOrCopyFile(arg1, arg2, command == "mv");
            }
            else if (command == "grep")
            {
                fileManager.grepFile(arg1, arg2);
            }
        }
        else if (command == "rm" || command == "cat" || command == "touch")
        {
            if (command == "rm")
            {
                fileManager.removeFile(args);
            }
            else if (command == "cat")
            {
                fileManager.catFile(args);
            }
            else if (command == "touch")
            {
                fileManager.touchFile(args);
            }
        }
        else
        {
            cerr << "Unknown command: " << command << "\n";
        }
    }
    else
    {
        cerr << "Invalid command. Please provide valid input.\n";
    }
}

// Main function
int main()
{
    FileManager fileManager;

    while (true)
    {
        
        cout << "Enter command (or 'exit' to quit): ";
        string userInput;
        getline(cin, userInput);

        
        if (userInput == "exit")
        {
            break;
        }

        processCommand(userInput, fileManager);
    }

    return 0;
}
