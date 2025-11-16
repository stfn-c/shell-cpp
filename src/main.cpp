#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::function<int(const std::vector<std::string> &)>> commands;

int cmd_exit(const std::vector<std::string> &args) {
    std::exit(0);
    return 0;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    commands = {{"exit", cmd_exit}};

    while (true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> args;

        int idx = 0;
        int count = 0;

        for (int i = 0; i < input.size(); i++) {
            if (input[i] == ' ') {
                if (count > 0)
                    args.push_back(input.substr(idx, count));

                idx = i + 1;
                count = 0;
            } else {
                count++;
            }
        }
        if (count > 0)
            args.push_back(input.substr(idx, count));

        if (commands.count(args[0]) == 0) {
            std::cout << input << ": command not found\n";
        } else {
            commands[args[0]](args);
        }
    }
}
