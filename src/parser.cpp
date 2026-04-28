#include "parser.hpp"
#include <iostream>

Parser::Parser(std::vector<Token> t) : tokens(std::move(t)) {}

std::optional<ParsedPipeline> Parser::parse() {
    ParsedPipeline out;
    std::vector<std::string> cur;
    bool need_command_after_pipe = false;

    const auto flush = [&] {
        if (!cur.empty())
            out.stages.push_back(std::move(cur));
        cur.clear();
    };

    for (; pos < tokens.size(); ++pos) {
        const Token& tk = tokens[pos];
        switch (tk.type) {
        case TokenType::WORD:
        case TokenType::NUMBER:
            need_command_after_pipe = false;
            cur.push_back(tk.value);
            break;
        case TokenType::PIPE:
            if (cur.empty()) {
                std::cerr << "myshell: syntax error near unexpected token `|'\n";
                return std::nullopt;
            }
            flush();
            need_command_after_pipe = true;
            break;
        default:
            std::cerr << "myshell: parse error (token `" << tk.value << "')\n";
            return std::nullopt;
        }
    }

    flush();

    if (need_command_after_pipe) {
        std::cerr << "myshell: syntax error: incomplete pipe\n";
        return std::nullopt;
    }

    if (out.stages.empty())
        return std::nullopt;
    return out;
}
