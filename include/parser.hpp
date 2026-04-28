#pragma once
#include "lexer.hpp"
#include "pipeline.hpp"
#include <optional>
#include <vector>

class Parser {
    std::vector<Token> tokens;
    std::size_t pos = 0;

public:
    explicit Parser(std::vector<Token> t);
    Parser(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser& operator=(Parser&&) = delete;

    [[nodiscard]] std::optional<ParsedPipeline> parse();
};
