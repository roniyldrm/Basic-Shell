#include "include/lexer.hpp"

Lexer::Lexer(const std::string& text) : text(text){};

std::optional<std::vector<Token>> Lexer::tokenize(){ 
    std::vector<Token> tokens;
    auto&& t{this->text};
    
    if(t.empty()) 
        return {};

    while(pos < t.length()){
        auto&& c{t[pos]};
        

        if(std::isspace(c)){
            pos++;
        }
        
        if(std::isalpha(c) && (c != '\"' || c != '\'')){
            std::string s;
            while(!std::isspace(t[pos]) && pos < t.length()){
                s += t[pos];
                pos++;
            }
            tokens.push_back({TokenType::WORD, std::move(s)});
        }else if(c == '\"' || c == '\'' && pos < t.length()){
            std::string s;
            pos++;
            while(!(t[pos] == '\"' || t[pos] == '\'') && pos < t.length()){
                s += t[pos];
                pos++;
            }
            tokens.push_back({TokenType::WORD, std::move(s)});
        }else if(std::isdigit(c)){
            std::string s;
            while(!std::isdigit(t[pos]) && pos < t.length()){
                s += t[pos];
                pos++;
            }
            tokens.push_back({TokenType::NUMBER, std::move(s)});
        }

        // ...
        return {tokens};
    }
}