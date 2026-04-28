#include "builtins.hpp"
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace {

void ls_print_dir(const fs::path& p) {
    std::vector<std::string> names;
    for (const auto& entry : fs::directory_iterator(p))
        names.push_back(entry.path().filename().string());
    std::sort(names.begin(), names.end());
    for (const auto& name : names)
        std::cout << name << '\n';
}

} // namespace

int builtin_cd(const std::vector<std::string>& args) {
    std::string path;
    if (args.size() > 1)
        path = args[1];
    else {
        const char* home = std::getenv("HOME");
        if (!home) {
            std::cerr << "cd: HOME not set\n";
            return 1;
        }
        path = home;
    }

    std::error_code ec;
    fs::current_path(path, ec);
    if (ec) {
        std::cerr << "cd: " << path << ": " << ec.message() << '\n';
        return 1;
    }
    return 0;
}

int builtin_pwd(const std::vector<std::string>& args) {
    (void)args;
    std::error_code ec;
    const fs::path cwd = fs::current_path(ec);
    if (ec) {
        std::cerr << "pwd: " << ec.message() << '\n';
        return 1;
    }
    std::cout << cwd.string() << '\n';
    return 0;
}

int builtin_echo(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); ++i) {
        if (i > 1)
            std::cout << ' ';
        std::cout << args[i];
    }
    std::cout << '\n';
    return 0;
}

int builtin_ls(const std::vector<std::string>& args) {
    try {
        if (args.size() == 1) {
            ls_print_dir(fs::current_path());
            return 0;
        }

        for (size_t i = 1; i < args.size(); ++i) {
            if (i > 1)
                std::cout << '\n';
            const fs::path p(args[i]);
            std::cout << args[i] << ":\n";
            if (!fs::exists(p)) {
                std::cerr << "ls: cannot access '" << args[i] << "'\n";
                continue;
            }
            if (!fs::is_directory(p)) {
                std::cout << args[i] << '\n';
                continue;
            }
            ls_print_dir(p);
        }
        return 0;
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "ls: " << ex.what() << '\n';
        return 1;
    }
}

int builtin_help(const std::vector<std::string>& args) {
    (void)args;
    std::cout << R"(Built-in commands:
  cd [dir]     change directory (default: $HOME)
  pwd          print working directory
  echo [args]  print arguments
  ls [dirs]    list directory entries (directory_iterator)
  help         show this text
  exit [n]     leave the shell with status n (default: last status)
)";
    return 0;
}
