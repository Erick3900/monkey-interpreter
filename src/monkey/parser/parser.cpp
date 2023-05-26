#include "parser/parser.hpp"

namespace arti::monkey {

    Parser::Parser(std::unique_ptr<Lexer> lexer)
        : lexer(std::move(lexer))
        , tokensGenerator{}
        , tokensIterator{}
        , currentToken{}
        , peekToken{} {
        if (not this->lexer) {
            throw std::runtime_error("Lexer provided to Parser is not valid");
        }

        tokensGenerator = lexer->tokensIterator();
        tokensIterator = tokensGenerator.begin();

        nextToken();
        nextToken();
    }

    void Parser::nextToken() {
        currentToken = peekToken;
        peekToken = *tokensIterator;
        ++tokensIterator;
    }

}
