#pragma once
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// Get all valid directories from PATH environment variable
std::vector<fs::path> get_path_directories();

// Check if a file is executable
bool is_executable(const fs::path &path);

// Search for an executable in PATH directories
std::optional<fs::path> find_executable_in_path(const std::string &command);

// Returns current path
fs::path get_current_path();
