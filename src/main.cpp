#pragma once
#include "builtin_commands.hpp"
#include "path_utils.hpp"
#include "process_utils.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> args;

        size_t idx = 0;
        size_t count = 0;

        for (size_t i = 0; i < input.size(); i++) {
            if (input[i] == ' ') {
                if (count > 0) {
                    args.push_back(input.substr(idx, count));
                }

                idx = i + 1;
                count = 0;
            } else {
                count++;
            }
        }

        if (count > 0) {
            args.push_back(input.substr(idx, count));
        }

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
