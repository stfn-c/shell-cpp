#include "builtin_commands.hpp"
#include "path_utils.hpp"
#include <cstdlib>
#include <iostream>

const std::unordered_map<std::string, std::function<int(const std::vector<std::string> &)>>
    builtin_commands = { { "exit", builtin_exit },
                         { "echo", builtin_echo },
                         { "type", builtin_type } };

[[noreturn]] int builtin_exit(const std::vector<std::string> &args) {
    std::exit(0);
}

int builtin_echo(const std::vector<std::string> &args) {
    bool first = true;

    for (const std::string &arg : args) {
        if (!first) {
            std::cout << " ";
        }

        std::cout << arg;
        first = false;
    }

    std::cout << "\n";

    return 0;
}

int builtin_type(const std::vector<std::string> &args) {
    if (args.empty()) {
        return 1;
    }

    if (builtin_commands.find(args[0]) != builtin_commands.end()) {
        std::cout << args[0] << " is a shell builtin\n";
        return 0;
    }

    std::optional<fs::path> found_executable = find_executable_in_path(args[0]);

    if (found_executable.has_value()) {
        // is found, return
        std::cout << args[0] << " is " << found_executable.value().string() << "\n";
        return 0;
    }

    std::cout << args[0] << ": not found\n";

    return 1;
}
