#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <optional>

enum class TokenType{
    WORD,
    NUMBER,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    AND,
    OR,
    SEMICOLON,
    END_OF_FILE
};

struct Token{
    TokenType type;
    std::string value;
};


class Lexer{

    std::string_view text;
    
public:
    std::size_t pos = 0;
    
    Lexer(const std::string& text);

    [[nodiscard]] 
    std::optional<std::vector<Token>> tokenize();

};
