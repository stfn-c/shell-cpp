#include "builtin_commands.hpp"
#include "path_utils.hpp"
#include "shell_state.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>

const std::unordered_map<std::string, std::function<int(const std::vector<std::string> &)>>
    builtin_commands = { { "exit", builtin_exit },
                         { "echo", builtin_echo },
                         { "type", builtin_type },
                         { "pwd", builtin_pwd },
                         { "cd", builtin_cd } };

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

int builtin_pwd(const std::vector<std::string> &args) {
    std::cout << shell_state.current_directory.string() << "\n";

    return 0;
}

int builtin_cd(const std::vector<std::string> &args) {
    fs::path target_dir;

    if (args.empty()) {
        const char *home = std::getenv("HOME");

        if (!home) {
            std::cerr << "cd: HOME not set\n";
            return 1;
        }

        target_dir = home;
    } else {
        target_dir = args[0];
    }

    if (!target_dir.is_absolute()) {
        target_dir = shell_state.current_directory / target_dir;
    }

    if (!fs::exists(target_dir)) {
        std::cerr << "cd: " << args[0] << ": No such file or directory\n";
        return 1;
    }

    if (!fs::is_directory(target_dir)) {
        std::cerr << "cd: " << args[0] << ": Not a directory\n";
        return 1;
    }

    shell_state.update_directory(target_dir);

    return 0;
}
