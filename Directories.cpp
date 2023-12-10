#pragma once
#include <string>
using namespace std;

class Directories
{
public:
	virtual bool cd(const std::string& desiredDirectory) = 0;
	virtual void mkdir(const std::string& directory_name) = 0;
	virtual void pwd() = 0;
	virtual void rmdir(const std::string& directoryPath) = 0;
	virtual void ls(const std::string& path = ".") = 0;
	virtual string getPath() = 0;
};