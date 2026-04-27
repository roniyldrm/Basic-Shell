#pragma once
#include "headers.hpp"

// std::monostate = "no value" (std::variant cannot use void as a type)
class Shell{
    using builtInResult = std::variant<std::monostate, int, bool, std::string>;
    using builtInFunc = std::function<builtInResult(const std::vector<std::string>&)>;
    
public:
    Shell();
    ~Shell();

    Shell(const Shell&) = delete;
    Shell& operator=(const Shell&) = delete;

    void run();

    std::map<std::string, builtInFunc> builtins;
    void registerBuiltins();

    /// Runs argv[0] via execvp in a child process; parent waits for it.
    void executeExternal(const std::vector<std::string>& args);
    std::optional<std::vector<std::string>> tokenize(const std::string& line);
};

class Process{
    pid_t pid;
public:
    int operator()();
    Process(pid_t p);
    ~Process();
};
