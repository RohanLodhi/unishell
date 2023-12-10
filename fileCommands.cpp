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
    bool removeFile(const string& filename)
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

    void catFile(const string filename)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            file.seekg(0, ios::end);
            long long length = file.tellg();
            if (length == 0)
            {
                cout << "The file " << filename << " is empty" << endl;
            }    
            else
            {
                file.seekg(0, ios::beg);
                cout << "Contents of file '" << filename << "':\n";
                cout << file.rdbuf() << endl;

            }
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
    void touchFile(const string& filename)
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
    bool moveOrCopyFile(const string& source, const string& destination, bool isMove)
    {
        ifstream sourceFile(source, ios::binary);
        

        if (sourceFile.is_open())
        {
            if (sourceFile.peek() == ifstream::traits_type::eof())
            {

                cerr << "The source file is empty" << endl;
                sourceFile.close();
                return false;
            }
            else
            {
                ofstream destFile(destination, ios::binary);
                if (destFile.is_open())
                {
                    destFile << sourceFile.rdbuf();
                    sourceFile.close();
                    if (isMove)
                        removeFile(source);
                    destFile.close();
                }
                else
                {
                    cerr << "Error " << (isMove ? "moving" : "copying") << " file from '" << source << "' to '" << destination << "'.\n";
                    return false;
                }
            }

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
    void grepFile(const string& filename, const string& searchString)
    {
        ifstream file(filename);
        if (file.is_open())
        {
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
