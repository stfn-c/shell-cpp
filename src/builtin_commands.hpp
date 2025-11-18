#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

[[noreturn]] int builtin_exit(const std::vector<std::string> &args);
int builtin_echo(const std::vector<std::string> &args);
int builtin_type(const std::vector<std::string> &args);
int builtin_pwd(const std::vector<std::string> &args);
int builtin_cd(const std::vector<std::string> &args);

extern const std::unordered_map<std::string, std::function<int(const std::vector<std::string> &)>>
    builtin_commands;
