#pragma once
#include "lexer.hpp"
#include <memory>
#include <string>
#include <vector>

struct ASTNode{
    std::string value;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    explicit ASTNode(std::string s = "");
    ASTNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r, std::string s = "");
};

class Parser{
private:
    std::vector<Token> tokens;
    std::size_t pos = 0;

    Token& current();
    void pass();

public:
    explicit Parser(std::vector<Token> t);
    Parser() = delete;
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;

    Parser& operator=(const Parser&) = delete;
    Parser& operator=(Parser&&) = delete;

    /// Minimal stub: parses a pipeline / tree later; yields a trivial node when possible.
    [[nodiscard]] std::unique_ptr<ASTNode> parse();
};
