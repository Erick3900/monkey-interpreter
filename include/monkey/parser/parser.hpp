#pragma once

#include <optional>

#include "ast/ast.hpp"
#include "token/token.hpp"
#include "lexer/lexer.hpp"

namespace arti::monkey {

    struct Parser {
        std::unique_ptr<Lexer> lexer;

        nstd::generator<Token> tokensGenerator;
        nstd::generator<Token>::iterator tokensIterator;

        Token currentToken;
        Token peekToken;

        Parser(std::unique_ptr<Lexer> lexer);

        Parser() = delete;
        ~Parser() = default;

        Parser(Parser &&) = default;
        Parser(const Parser &) = delete;

        Parser &operator=(Parser &&) = default;
        Parser &operator=(const Parser &) = delete;

        void nextToken();
    };

}
