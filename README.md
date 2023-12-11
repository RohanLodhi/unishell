# Unishell - Platform-Independent UNIX Bash Implementation

Welcome to Unishell, a simple platform-independent UNIX-like shell implemented in C++. This shell provides basic functionality for common commands and supports execution of arbitrary commands using the `system()` function.

## Supported Commands:

- **cd**: Change directory.
- **pwd**: Present working directory.
- **ls**: List items in the current directory.
- **mkdir**: Make directory.
- **rmdir**: Remove directory.
- **ls -a**: List all items in the current directory.
- **cp**: Copy file.
- **rm**: Remove file.
- **mv**: Move file.
- **cat filename**: Display the content of the file.
- **whoami**: Show your username.
- **ifconfig**: Print network information.
- **echo**: Print a command. Use `echo >> file.txt` to print to a file.

If a command is not directly supported, the `system()` function is used to execute the command.

## Instructions for Building and Running:

An executable is available for direct uplaod, however, if you wish ypu can build the program yourself. Follow these steps to build and run the Unishell program:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/rohanlodhi/unishell.git
   cd unishell
2. **Create a Build Directory:**
    ```
    mkdir build
    cd build
3. **Run CMake:**

    ```bash
    cmake ../
4. **Build the Executable:**

    ```bash
    make
5. **Run Unishell:**

    ```bash
    ./unishell
Platform-Specific Source Files:

The source files are organized based on the operating system. If you are on Windows, the Windows-specific files will be used, and if you are on Linux, the Linux-specific files will be used.

Windows Files:

    Directory Commands: windows/directory commands/DirectoryCommandsWindows.cpp
    Network Commands: windows/network commands/networkCommandsWindows.cpp
    System Commands:
        windows/system commands/Hardware.cpp
        windows/system commands/HelperFunctions.cpp
        windows/system commands/Time.cpp
        windows/system commands/WindowsInfo.cpp
        windows/system commands/WindowsSystem.cpp

Linux Files:

    Directory Commands: linux/directory commands/DirectoryCommandsLinux.cpp
    Network Commands: linux/network commands/networkCommandsLinux.cpp
    System Commands:
        linux/system commands/LinuxHardware.cpp
        linux/system commands/LinuxInfo.cpp
        linux/system commands/LinuxSystem.cpp
        linux/system commands/Time.cpp

