#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

int main() {
  char tmp[256];  // temp array to store the current working directory 

  // get the current working directory
  getcwd(tmp, 256);
  cout << "Current working directory: " << tmp << endl;

  return EXIT_SUCCESS;
}