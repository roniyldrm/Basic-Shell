#include <string>
#include <vector>
#include <optional>

enum class TokenType{
    WORD,
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

    std::string text;
    std::size_t pos = 0;
    
public:
    Lexer(const std::string& text);

    [[nodiscard]] 
    std::optional<std::vector<std::string>> tokenize() const;

};