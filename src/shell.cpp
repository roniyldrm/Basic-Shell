#include "shell.hpp"
#include "builtins.hpp"



void Shell::run() const{
 while (true) {
        std::cout << "myshell> ";

        std::string input;
        if (!std::getline(std::cin, input))
            break;

    /*
        auto tokens = lexer.tokenize(input);
        auto ast = parser.parse(tokens);
        executor.execute(ast);
    */

 }
}


void Shell::registerBuiltins(){
    builtins["test"] = test;
}

void Shell::executeExternal(const std::vector<char *>& tokens){
    Process p{fork()};

    if(p() > 0){
        execvp(tokens[0], tokens.data());

        perror("exec failed");
        exit(1);
    }
}

std::optional<std::vector<std::string>> Shell::tokenize(const std::string& line){
    
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
        tokens.push_back(token);

    
    return tokens.empty() ? std::optional<std::vector<std::string>>{tokens} : std::optional<std::vector<std::string>>{};
}


Process::Process(pid_t p) : pid(p){}

int Process::operator()(){
    return this->pid;
}

Process::~Process(){
    if (pid > 0){ waitpid(pid, nullptr, 0);}
}
