#include <iostream>
#include <string>

using namespace std;

#if defined(_WIN32)
#include <direct.h>  // For windows
#define mkdir_function _mkdir
#else
#include <sys/stat.h> // For linux or macOS
#define mkdir_function mkdir
#endif

int main() {
    // Array to store names of created directories
    string list_of_directories[20];

    // User input for folder name
    string folder_name_input_string;

    // Counter to keep track of the number of directories created
    int counter = 0;

    cout << "Please enter the Name of the folder: ";
    cin >> folder_name_input_string;

    // Attempt to create the directory using the platform-specific mkdir function
    if (mkdir_function(folder_name_input_string.c_str()) == 0) {
        cout << "Folder created successfully." << endl;
        list_of_directories[counter] = folder_name_input_string;
        counter++;
        folder_name_input_string = "";

    } else {
        cerr << "Error creating folder. Try choosing a different folder name." << endl;
        folder_name_input_string = "";
    }

    return 0;
}
