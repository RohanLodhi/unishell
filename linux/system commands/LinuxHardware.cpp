#include "LinuxHardware.h"

using namespace std;

LinuxHardware :: LinuxHardware() : mCpuName(""), mMemory(""), mDisplayResolution(""), mTotalMemory(0), mUtilizedMemory(0)
{
    FindDisplayResolution();
    FindCpuName();
    FindGpuNames();
}

int LinuxHardware :: FindGpuNames()
{
    string gpuCodes[2] = {"3D", "VGA"};

    for (int i = 0; i < gpuCodes->size(); i ++)
    {
        // Command to execute (replace 'your_pattern' and 'your_file' with actual values)
        const string command = ("lspci -v | grep " + gpuCodes[i]);

        // Open a pipe to the command
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            cout << "popen() failed!" << std::endl;
            return EXIT_FAILURE;
        }

        // Buffer to store the output
        char buffer[128];
        std::string result;

        // Read the output of the command
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {    
            result += buffer;
        }

        // Close the pipe

        int status = pclose(pipe);
        if (status == -1) {
            cout << "pclose() failed!" << std::endl;
            return EXIT_FAILURE;
        }

        // Print or process the captured output
        //cout << "Output of grep command:\n" << result;

        size_t start = result.find(": ") + 2;
        size_t end = result.find(" (rev");

        if (start != string :: npos && end != string :: npos) {
            //cout << result.substr(start, end - start);
            mGpuNames.push_back(result.substr(start, end - start));
        } else {
            cout << "\nError: Unable to extract GPU name.";
        }

    }
    return EXIT_SUCCESS;

}

int LinuxHardware :: FindCpuName()
{
    const char *path = "/proc/cpuinfo";
    ifstream cpuFile(path);
    if (!cpuFile.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return EXIT_FAILURE;
    }
    string line;
    while (getline(cpuFile, line)) {
        if (line.substr(0, 10) == "model name")
        {
            size_t start = line.find(":");
            mCpuName =  line.substr(start + 2);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int LinuxHardware::FindAvailableMemory()
{
    const char *path = "/proc/meminfo";
    ifstream memFile(path);
    if (!memFile.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return EXIT_FAILURE;
    }
    string line;
    while (getline(memFile, line)) {
        if (line.substr(0, 8) == "MemTotal")
        {
            size_t start = line.find_first_of("0123456789");
            line = line.substr(start, line.find_first_not_of("0123456789", start) - start);
            mTotalMemory = stoi(line) / 1024;
        }
        else if (line.substr(0, 12) == "MemAvailable")
        {
            size_t start = line.find_first_of("0123456789");
            line = line.substr(start, line.find_first_not_of("0123456789", start) - start);
            mUtilizedMemory = mTotalMemory - (stoi(line) / 1024);
        }
    }
    cout << to_string(mUtilizedMemory) + "MiB / " + to_string(mTotalMemory) + "MiB";


    return EXIT_SUCCESS;
}

int LinuxHardware::FindDisplayResolution()
{
    const char *path = "/sys/class/graphics/fb0/modes";
    ifstream displyFile(path);
    if (!displyFile.is_open())
    {
        cerr << "Error: Unable to open the file." << endl;
        return EXIT_FAILURE;
    }
    string line;
    getline(displyFile, line);
    if(line.size() > 0)
    {
        size_t splitter = line.find(":");
        if(splitter < line.size())
        {
            line = line.substr(splitter+1);
        }
        splitter = line.find("-");
        if (splitter < line.size())
        {
            line = line.substr(0, splitter);
        }
        mDisplayResolution = line;
    }
    else{
        cerr << "Error: The file was empty";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


string LinuxHardware::GetCpuName() const
{
    return mCpuName;
}

vector<string> LinuxHardware::GetGpuNames() const
{
    return mGpuNames;
}

string LinuxHardware::GetMemoryUtilization()
{
    FindAvailableMemory();
    return mMemory;
}

string LinuxHardware::GetDisplayResolution() const
{
    return mDisplayResolution;
}