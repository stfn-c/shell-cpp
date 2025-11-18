#include "builtin_commands.hpp"
#include "path_utils.hpp"
#include "process_utils.hpp"
#include "shell_state.hpp"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

ShellState shell_state;

std::vector<std::string> parse_args(const std::string &input) {
    std::vector<std::string> args;
    std::string current_arg;
    bool in_quotes = false;

    for (char c : input) {
        if (c == '\'' && in_quotes) {
            in_quotes = false;
        } else if (c == '\'' && !in_quotes) {
            in_quotes = true;
        } else if (!in_quotes && c == ' ') {
            if (!current_arg.empty()) {
                args.push_back(current_arg);
                current_arg = "";
            }
        } else {
            current_arg += c;
        }
    }

    if (!current_arg.empty()) {
        args.push_back(current_arg);
    }

    return args;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> args = parse_args(input);

        if (args.empty()) {
            continue;
        }

        const auto it = builtin_commands.find(args[0]);
        if (it != builtin_commands.end()) {
            std::vector<std::string> cmd_args(args.begin() + 1, args.end());
            it->second(cmd_args);
            continue;
        } else {
            std::optional<fs::path> found_executable = find_executable_in_path(args[0]);

            if (found_executable.has_value()) {
                const std::string path_to_executable = found_executable.value().string();

                execute_command(path_to_executable, args);
                continue;
            }
        }

        std::cout << args[0] << ": command not found\n";
    }

    return 0;
}
