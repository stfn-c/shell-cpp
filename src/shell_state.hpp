#pragma once
#include <filesystem>

namespace fs = std::filesystem;

struct ShellState {
    fs::path current_directory;

    ShellState() : current_directory(fs::current_path()) {
    }

    void update_directory(const fs::path &new_dir) {
        current_directory = new_dir;
        fs::current_path(new_dir);
    }
};

extern ShellState shell_state;
