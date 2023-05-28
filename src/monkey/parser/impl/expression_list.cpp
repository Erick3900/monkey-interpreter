#include "parser/parser.hpp"

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<std::vector<ASTNode *>, std::string> Parser::parseExpressionList(Program *program) {
        std::vector<ASTNode *> expressions;

        nextToken();

        if (currentTokenIs(tokens::RBracket.type)) {
            return expressions;
        }

        tl::expected<ASTNode *, std::string> expectedExpression;

        expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedExpression) {
            return tl::unexpected{ std::move(expectedExpression).error() };
        }

        expressions.push_back(expectedExpression.value());

        while (peekTokenIs(tokens::Comma.type)) {
            nextToken();
            nextToken();

            expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

            if (not expectedExpression) {
                return tl::unexpected{ std::move(expectedExpression).error() };
            }

            expressions.push_back(expectedExpression.value());
        }

        if (auto expected = expectPeek(tokens::RBracket.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return expressions;
    }
}

