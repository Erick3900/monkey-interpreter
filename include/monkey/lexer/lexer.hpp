#pragma once

#include <filesystem>
#include <fstream>

#include "utils/coroutines.hpp"

#include "token/token.hpp"

namespace arti::monkey {

    struct Lexer {
        std::size_t lineCount;
        std::size_t position;
        std::string sourceCode;
        std::filesystem::path sourcePath;
        std::unique_ptr<std::istream> sourceStream;

        Lexer(std::filesystem::path filepath);
        Lexer(std::unique_ptr<std::istream> sourceStream);

        Lexer() = delete;
        ~Lexer() = default;

        Lexer(Lexer &&) = default;
        Lexer(const Lexer &) = delete;

        Lexer &operator=(Lexer &&) = default;
        Lexer &operator=(const Lexer &) = delete;

        nstd::generator<Token> tokensIterator();
    };

}    // namespace arti::monkey
