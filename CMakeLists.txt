cmake_minimum_required(VERSION 3.12)
project(unishell)

set(CMAKE_CXX_STANDARD 17)

# Add the source files
set(SOURCES
    Directories.cpp
    echo.cpp
    parsing.cpp
    fileCommands.cpp
)

# Check for the operating system
if(WIN32)
    # Windows-specific source files
    list(APPEND SOURCES windows/directory\ commands/DirectoryCommandsWindows.cpp
    windows/network\ commands/networkCommandsWindows.cpp
    windows/system\ commands/Hardware.cpp
    windows/system\ commands/HelperFunctions.cpp
    windows/system\ commands/Time.cpp
    windows/system\ commands/WindowsInfo.cpp
    windows/system\ commands/WindowsSystem.cpp)
else()
    # Linux-specific source files
    list(APPEND SOURCES linux/directory\ commands/DirectoryCommandsLinux.cpp
    linux/network\ commands/networkCommandsLinux.cpp
    linux/system\ commands/LinuxHardware.cpp
    linux/system\ commands/LinuxInfo.cpp
    linux/system\ commands/LinuxSystem.cpp
    linux/system\ commands/Time.cpp)
endif()

# Create the executable in the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
add_executable(${PROJECT_NAME} ${SOURCES})