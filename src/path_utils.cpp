#include "path_utils.hpp"
#include <cstdlib>
#include <sstream>

#ifdef _WIN32
constexpr char PATH_DELIMITER = ';';
#else
constexpr char PATH_DELIMITER = ':';
#endif

std::vector<fs::path> get_path_directories() {
    const char *path_env = std::getenv("PATH");
    if (!path_env) {
        return {};
    }

    std::vector<fs::path> directories;
    std::stringstream ss{ path_env };
    std::string directory;

    while (std::getline(ss, directory, PATH_DELIMITER)) {
        if (directory.empty()) {
            continue;
        }

        if (fs::exists(directory) && fs::is_directory(directory)) {
            directories.push_back(directory);
        }
    }

    return directories;
}

bool is_executable(const fs::path &path) {
    if (!fs::exists(path) || !fs::is_regular_file(path)) {
        return false;
    }

    auto perms = fs::status(path).permissions();

    return (perms & fs::perms::owner_exec) != fs::perms::none ||
           (perms & fs::perms::group_exec) != fs::perms::none ||
           (perms & fs::perms::others_exec) != fs::perms::none;
}

std::optional<fs::path> find_executable_in_path(const std::string &command) {
    auto directories = get_path_directories();

    for (const auto &dir : directories) {
        fs::path full_path = dir / command;
        if (is_executable(full_path)) {
            return full_path;
        }
    }

    return std::nullopt;
}
