#include "LinuxSystem.h"

using namespace std;

LinuxSystem::LinuxSystem() : mHostName(""), mUserName(""), mModel("")
{
    mDevice = LinuxHardware();
    mLinux = LinuxInfo();
    FindHostName();
    FindUserName();
    FindModelName();
}

int LinuxSystem::FindHostName()
{
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    mHostName = hostname;
    return EXIT_SUCCESS;
}

int LinuxSystem::FindUserName()
{
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    mUserName = username;
    return EXIT_SUCCESS;
}

int LinuxSystem::Neofetch()
{
    cout << "              a8888b.               " << endl;
    cout << "             d888888b.              " << endl;
    cout << "             8P\"YP\"Y88              " << endl;
    cout << "             8|o||o|88              " << endl;
    cout << "             8'    .88              " << endl;
    cout << "             8`._.' Y8.             " << endl;
    cout << "            d/      `8b.            " <<mUserName << "@" << mHostName << endl;
    cout << "           dP   .    Y8b.           " << "------------------------------------------" << endl;
    cout << "          d8:'  \"  `::88b           " << "OS: " << mLinux.GetOsName() << endl;
    cout << "         d8\"         'Y88b          " << "Host: " << mModel << endl;
    cout << "        :8P    '      :888          " << "Kernel: " << mLinux.GetKernelVersion() << endl;
    cout << "         8a.   :     _a88P          " << "Uptime: " << mLinux.GetUptime() << endl;
    cout << "       ._/\"Yaa_:   .| 88P|          " << "Shell: " << mShell << endl;
    cout << "       |    YP\"    `| 8P  `.        " << "Resolution: " << mDevice.GetDisplayResolution() << endl;
    cout << "       /     `.___.d|      /        " <<"CPU: " << mDevice.GetCpuName() << endl;
    cout << "       `--..__)8888P`.__.'          ";
    auto gpuNames = mDevice.GetGpuNames();
    for (int i = 0; i < gpuNames.size(); i ++)
    {
        if (i == 0)
            cout << "GPU: " << gpuNames[i] << endl;
        else 
            cout << "                                    " <<  "GPU: " << gpuNames[i] << endl;
    }
    cout << "                                    " << "Memory " << mDevice.GetMemoryUtilization() << endl << endl << endl;

    return EXIT_SUCCESS;
}

int LinuxSystem::WhoAmI()
{
    cout << mUserName;
    return EXIT_SUCCESS;
}

int LinuxSystem::FindModelName()
{
    const string file[2] = {"product_name", "sys_vendor"};

    string manufacturer;
    string model;

    for (int i = 0; i < 2; i ++)
    {
        string path = "/sys/class/dmi/id/" + file[i];
        ifstream sysInfoFilePath(path);
        if (!sysInfoFilePath.is_open()) 
        {
            cerr << "Error: Unable to open the file." << endl;
            return EXIT_FAILURE;
        }
        string line;
        getline(sysInfoFilePath, line);
        try
        {
            if(file[i] == "product_name")
                model = line;
            else 
                manufacturer = line;
        }
        catch (...)
        {
            cerr << "\nFile with path: " << file << " does not exist";
            return EXIT_FAILURE;
        }
    }
    mModel = manufacturer + " " + model;
    return EXIT_SUCCESS;
}