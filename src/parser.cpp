#include "parser.hpp"

ASTNode::ASTNode(std::string s) : value(std::move(s)), left(nullptr), right(nullptr) {}

ASTNode::ASTNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r, std::string s)
    : value(std::move(s)), left(std::move(l)), right(std::move(r)) {}

void Parser::pass() {
    ++pos;
}

Token& Parser::current() {
    return tokens[pos];
}

Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

std::unique_ptr<ASTNode> Parser::parse() {
    if (tokens.empty() || pos >= tokens.size())
        return nullptr;
    // Stub for future pipeline / redirect AST; no piping yet.
    return std::make_unique<ASTNode>(tokens[pos].value);
}
