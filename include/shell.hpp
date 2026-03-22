#include "headers.hpp"



class Shell{
    using builtInResult = std::variant<void, int, bool, std::string>;
    using builtInFunc = std::function<builtInResult(const std::vector<std::string>&)>;
    
public:
    Shell();
    ~Shell();

    Shell(const Shell&) = delete;
    Shell& operator=(const Shell&) = delete;

    void run() const;

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
