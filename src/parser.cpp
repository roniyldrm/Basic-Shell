#include "include/parser.hpp"

ASTNode::ASTNode(const std::string& s = "") : left(nullptr), right(nullptr), value(std::move(s)){}

ASTNode::ASTNode(ASTNode* l, ASTNode* r, const std::string& s = "") : left(l), right(r), value(std::move(s)){}

constexpr void Parser::pass() { this->pos++;}

constexpr Token& Parser::current() { return tokens[pos];}

Parser::Parser(const std::vector<Token>& t) : tokens(std::move(t)){}

ASTNode* Parser::parse(){

    
}