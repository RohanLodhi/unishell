#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std; 

void executeCommand(const string& command) {
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "Failed to fork." << endl;
        return;
    }

    if (pid == 0) {
        // Child process
        char* args[] = {(char*)command.c_str(), NULL};
        execvp(args[0], args);

        // execvp will only return if an error occurred.
        cerr << "Error executing command: " << command << endl;
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            cerr << "Command exited with error code: " << WEXITSTATUS(status) << endl;
        } else if (WIFSIGNALED(status)) {
            cerr << "Command was killed by signal: " << WTERMSIG(status) << endl;
        }
    }
}
