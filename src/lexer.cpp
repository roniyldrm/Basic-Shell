#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& text) : text(text){}

std::optional<std::vector<Token>> Lexer::tokenize(){ 
    std::vector<Token> tokens;
    const auto t = this->text;
    
    if(t.empty())
        return std::nullopt;

    while(pos < t.length()){
        const unsigned char c = static_cast<unsigned char>(t[pos]);

        if(std::isspace(c)){
            pos++;
            continue;
        }

        if(c == '|'){
            tokens.push_back({TokenType::PIPE, "|"});
            pos++;
            continue;
        }

        if(c == '\"' || c == '\''){
            const char quote = static_cast<char>(c);
            std::string s;
            pos++;
            while(pos < t.length() && t[pos] != quote){
                s += t[pos];
                pos++;
            }
            if(pos < t.length() && t[pos] == quote)
                pos++;
            tokens.push_back({TokenType::WORD, std::move(s)});
            continue;
        }

        if(std::isdigit(c)){
            std::string s;
            while(pos < t.length() && std::isdigit(static_cast<unsigned char>(t[pos]))){
                s += t[pos];
                pos++;
            }
            tokens.push_back({TokenType::NUMBER, std::move(s)});
            continue;
        }

        std::string s;
        while(pos < t.length() && !std::isspace(static_cast<unsigned char>(t[pos]))){
            const char ch = t[pos];
            if (ch == '|' || ch == '\'' || ch == '\"')
                break;
            s += ch;
            pos++;
        }
        tokens.push_back({TokenType::WORD, std::move(s)});
    }

    if (tokens.empty())
        return std::nullopt;
    return tokens;
}
