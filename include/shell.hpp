#include "headers.hpp"


class Shell{
    using returnTypes = std::variant<void, int, bool, std::string>;
    using builtInFunc = std::function<returnTypes(const std::vector<std::string>&)>;

    Shell();
    void run();

public:
    std::map<std::string, builtInFunc> builtins;
    void registerBuiltins();
    
    void executeExternal(const std::vector<char *>& tokens);
    std::optional<std::vector<std::string>> tokenize(const std::string& line);
};

class Process{
    pid_t pid;

public:
    int operator()();
    Process(pid_t p);
    ~Process();
};