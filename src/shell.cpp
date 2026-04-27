#include "shell.hpp"
#include "builtins.hpp"

Shell::Shell() {
    registerBuiltins();
}

Shell::~Shell() = default;

void Shell::run() {
    while (true) {
        std::cout << "myshell> ";
        std::string input;
        if (!std::getline(std::cin, input))
            break;

        const auto words = tokenize(input);
        if (!words)
            continue;

        // Step 1: all commands go through the external path; builtin dispatch comes next.
        executeExternal(*words);
    }
}

void Shell::registerBuiltins() {
    builtins["test"] = [](const std::vector<std::string>& t) -> builtInResult {
        return test(t);
    };
}

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
        return;
    }
    if (child == 0) {
        execvp(argv[0], argv.data());
        perror("exec failed");
        _exit(127);
    }

    Process waiter{child};
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


Process::Process(pid_t p) : pid(p){}

int Process::operator()(){
    return this->pid;
}

Process::~Process(){
    if (pid > 0){ waitpid(pid, nullptr, 0);}
}
