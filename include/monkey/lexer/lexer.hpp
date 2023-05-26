#pragma once

#include <filesystem>
#include <fstream>

#include "utils/coroutines.hpp"

#include "token/token.hpp"

namespace arti::monkey {

    struct Lexer {
        using value_type = Token;
        using iterator = nstd::generator<Token>::iterator;
        using iterator_sentinel = nstd::generator<Token>::iterator_sentinel;

        std::size_t lineCount;
        std::size_t position;
        std::string sourceCode;
        std::filesystem::path sourcePath;
        std::unique_ptr<std::istream> sourceStream;

        nstd::generator<Token>::iterator tokensIterator;

        Lexer(std::filesystem::path filepath);
        Lexer(std::unique_ptr<std::istream> sourceStream);

        Lexer() = delete;
        ~Lexer() = default;

        Lexer(Lexer &&) = default;
        Lexer(const Lexer &) = delete;

        Lexer &operator=(Lexer &&) = default;
        Lexer &operator=(const Lexer &) = delete;

        void forward();
        Token nextToken();
        Token currentToken();

        nstd::generator<Token> &getIterator();

        iterator begin();
        iterator_sentinel end();

      private:
        nstd::generator<Token> init();

        nstd::generator<Token> tokensGenerator;
    };

}    // namespace arti::monkey
