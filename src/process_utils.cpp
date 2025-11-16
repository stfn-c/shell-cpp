#include "process_utils.hpp"
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int execute_command(const std::string &path, const std::vector<std::string> &args) {
    pid_t pid = fork();

    if (pid < 0) {
        // fork failed
        std::cerr << "Fork failed\n";
        return 1;
    }

    if (pid == 0) {
        // Child Process - execute the command
        std::vector<char *> c_args;

        for (const auto &arg : args) {
            c_args.push_back(const_cast<char *>(arg.c_str()));
        }
        c_args.push_back(nullptr);

        execv(path.c_str(), c_args.data());

        // If execv returns, it failed
        std::cerr << "Command execution failed\n";
        std::exit(1);

    } else {
        // Parent Process - wait for child to finish
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status); // Return child's exit code
        }

        return 1;
    }
}
