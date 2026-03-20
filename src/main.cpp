#include "include/built_in.hpp"

std::vector<std::string> tokenize(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token)
        tokens.push_back(token);

    return tokens;
}

int main(int argc, char** argv){ 

    while (true) {
        std::cout << "myshell> ";
        std::string input;
        std::getline(std::cin, input);

        const auto tokens = tokenize(input);

        if(tokens[0] == "cd"){
            if(std::filesystem::is_directory(tokens[1].c_str())){
                chdir(tokens[1].c_str());
                std::cout << std::filesystem::current_path() << "\n";
            }
            else{
                std::cout << "No such directory exists";
            }
        }

        if(tokens[0] == "exit")
            break;

        pid_t pid = fork();

        if (pid == 0)
        {
            std::vector<char *> args;
            for (auto &t : tokens)
                args.push_back(const_cast<char*>(t.data()));

            args.push_back(nullptr); //end of the arguments

            execvp(args[0], args.data());

            perror("exec failed");
            exit(1);
        }
        else
            waitpid(pid, nullptr, 0);
        

    }

}
