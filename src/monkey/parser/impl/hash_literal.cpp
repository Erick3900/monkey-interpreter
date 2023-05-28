#include "parser/parser.hpp"

#include <iostream>

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseHashLiteral(Program *program) {
        auto newLiteral = program->newNode<HashLiteral>();
        newLiteral->token = currentToken;

        while (not peekTokenIs(tokens::RSquirly.type)) {
            nextToken();

            ASTNode *key = nullptr;
            ASTNode *value = nullptr;

            if (currentTokenIs(tokens::LBracket.type)) {
                nextToken();

                if (not currentTokenIs(tokens::String.type)) {
                    return tl::unexpected<std::string>{ fmt::format("Expected StringLiteral as key but got: {}", currentToken.type) };
                }

                auto expectedString = parseStringLiteral(program);

                if (not expectedString) {
                    return expectedString;
                }

                key = expectedString.value();

                if (auto expected = expectPeek(tokens::RBracket.type); not expected) {
                    return tl::unexpected{ std::move(expected).error() };
                }
            }
            else {
                if (currentToken.type == tokens::String.type) {
                    return tl::unexpected<std::string>{ "Expected identifier, got string" };
                }

                auto expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

                if (not expectedExpression) {
                    return expectedExpression;
                }

                key = expectedExpression.value();
            }

            if (auto expected = expectPeek(tokens::Colon.type); not expected) {
                return tl::unexpected{ std::move(expected).error() };
            }

            nextToken();

            auto expectedValue = parseExpression(program, expressions::Precedence::LOWEST);

            if (not expectedValue) {
                return expectedValue;
            }

            value = expectedValue.value();

            newLiteral->elements.push_back({ key, value });

            if (not peekTokenIs(tokens::RSquirly.type) && not expectPeek(tokens::Comma.type)) {
                return tl::unexpected{
                    fmt::format("Expected next token to be '{}' or '{}', got: '{}'", 
                        tokens::RSquirly.type, 
                        tokens::Comma.type, 
                        peekToken.type
                    )
                };
            }
        }

        if (auto expected = expectPeek(tokens::RSquirly.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return newLiteral;
    }

}    // namespace arti::monkey
