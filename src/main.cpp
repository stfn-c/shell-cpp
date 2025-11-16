#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int cmd_exit(const std::vector<std::string> &args) {
    std::exit(0);
    return 0;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    const std::unordered_map<std::string, std::function<int(const std::vector<std::string> &)>>
        commands{{"exit", cmd_exit}};

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

        auto it = commands.find(args[0]);
        if (it == commands.end()) {
            std::cout << input << ": command not found\n";
        } else {
            it->second(args);
        }
    }

    return 0;
}
