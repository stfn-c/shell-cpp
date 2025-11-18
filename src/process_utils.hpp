#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int execute_command(const fs::path &path, const std::vector<std::string> &args);
