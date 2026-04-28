#pragma once
#include "headers.hpp"

class Shell{
    using BuiltinFunc = std::function<int(const std::vector<std::string>&)>;
public:
    Shell();
    ~Shell();

    Shell(const Shell&) = delete;
    Shell& operator=(const Shell&) = delete;

   
    int run();

    std::map<std::string, BuiltinFunc> builtins;
    void registerBuiltins();

    void executeExternal(const std::vector<std::string>& args);
    std::optional<std::vector<std::string>> tokenize(const std::string& line);

private:
    int builtinExit(const std::vector<std::string>& args);

    int last_status_{0};
    bool exit_requested_{false};
    int pending_exit_code_{0};
};
