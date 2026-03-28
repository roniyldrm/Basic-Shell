#include "lexer.hpp"

struct ASTNode{
    std::string value;
    ASTNode* left;
    ASTNode* right;

    ASTNode(ASTNode* l, ASTNode* r, const std::string& s = "");
};

class Parser{
private:
    std::vector<Token> tokens;
    std::size_t pos = 0;

    constexpr Token current() const;
    constexpr void pass();

public:
    Parser(const std::vector<Token>& t);
    Parser() = delete;
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;

    Parser& operator=(const Parser&) = delete;
    Parser& operator=(Parser&&) = delete;
};