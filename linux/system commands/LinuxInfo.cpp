#include "LinuxInfo.h"

using namespace std;

LinuxInfo :: LinuxInfo() : mUptime(""), mOsName(""), mKernelVersion("") 
{
    FindKernelVersion();
    FindOsName();
}

string LinuxInfo::GetKernelVersion() const
{
    return mKernelVersion;
}

string LinuxInfo::GetOsName() const
{
    return mOsName;
}

string LinuxInfo::GetUptime()
{
    CalculateUptime();
    return mUptime;
}

int LinuxInfo::CalculateUptime()
{
    const char *path = "/proc/uptime";
    int upTime = 0;
    ifstream upTimeFile(path);
    if (!upTimeFile.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return EXIT_FAILURE;
    }
    string line;
    while (getline(upTimeFile, line)) {
        size_t token = line.find(" ");
        upTime = stoi(line.substr(0, token + 1));
    }
    mUptime = Time::ConvertSecondsToHoursMinutesSeconds(upTime);
    
    return EXIT_FAILURE;
}

int LinuxInfo::FindOsName()
{
    struct utsname buf;
    try
    {
        uname(&buf);
        string OS = buf.version;
        size_t splitter = OS.find(" ");
        string osName = OS.substr(0, splitter);
        splitter = osName.find("~");
        mOsName = osName.substr(splitter + 1) + " " + buf.machine;    
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    
    return EXIT_SUCCESS;
}

int LinuxInfo::FindKernelVersion()
{
    struct utsname buf;
    try
    {
        uname(&buf);
        mKernelVersion = buf.release;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    
    return EXIT_SUCCESS;
}
