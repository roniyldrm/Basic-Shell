#include "shell.hpp"
#include "builtins.hpp"
#include <cstdlib>
#include <sys/wait.h>

Shell::Shell() {
    registerBuiltins();
}

Shell::~Shell() = default;

void Shell::registerBuiltins() {
    builtins["cd"] = builtin_cd;
    builtins["pwd"] = builtin_pwd;
    builtins["echo"] = builtin_echo;
    builtins["ls"] = builtin_ls;
    builtins["help"] = builtin_help;
    builtins["exit"] = [this](const std::vector<std::string>& args) {
        return builtinExit(args);
    };
}

int Shell::builtinExit(const std::vector<std::string>& args) {
    int code = last_status_;
    if (args.size() > 1) {
        try {
            const long v = std::stol(args[1], nullptr, 10);
            if (v < 0 || v > 255) {
                std::cerr << "exit: status out of range\n";
                return 1;
            }
            code = static_cast<int>(v);
        } catch (...) {
            std::cerr << "exit: numeric argument required\n";
            return 1;
        }
    }
    pending_exit_code_ = code;
    exit_requested_ = true;
    return code;
}

int Shell::run() {
    while (!exit_requested_) {
        std::cout << "myshell> ";

        std::string input;
        if (!std::getline(std::cin, input))
            break;

        const auto words = tokenize(input);
        if (!words)
            continue;

        const std::string& cmd = words->front();
        auto it = builtins.find(cmd);
        if (it != builtins.end())
            last_status_ = it->second(*words);
        else
            executeExternal(*words);

        // Let exit builtin terminate the shell after this iteration without double-running.
        if (exit_requested_)
            break;
    }

    if (exit_requested_)
        return pending_exit_code_;
    return last_status_;
}

std::optional<std::vector<std::string>> Shell::tokenize(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
        tokens.push_back(token);

    if (tokens.empty())
        return std::nullopt;
    return tokens;
}

namespace {

int wait_child_status(pid_t child) {
    int status = 0;
    if (::waitpid(child, &status, 0) < 0) {
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);

    return 1;
}

} // namespace

void Shell::executeExternal(const std::vector<std::string>& args) {
    if (args.empty())
        return;

    std::vector<char*> argv;
    argv.reserve(args.size() + 1);
    for (const auto& s : args)
        argv.push_back(const_cast<char*>(s.c_str()));
    argv.push_back(nullptr);

    const pid_t child = fork();
    if (child < 0) {
        perror("fork");
        last_status_ = 1;
        return;
    }
    if (child == 0) {
        execvp(argv[0], argv.data());
        perror("exec failed");
        _exit(127);
    }

    last_status_ = wait_child_status(child);
}
