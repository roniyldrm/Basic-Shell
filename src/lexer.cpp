#include "include/lexer.hpp"

Lexer::Lexer(const std::string& text) : text(text){};

std::optional<std::vector<std::string>> Lexer::tokenize() const{ 
    std::vector<std::string> tokens;
    auto&& t{this->text};

    if(this->text.empty()) 
        return {};

    while(pos < t.length()){
        auto&& c{t[pos]};


    }
}