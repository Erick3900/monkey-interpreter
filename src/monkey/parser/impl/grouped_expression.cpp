#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseGroupedExpression(Program *program) {
        nextToken();

        auto expressionExpected = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expressionExpected) {
            return expressionExpected;
        }

        if (auto expected = expectPeek(tokens::RParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return expressionExpected.value();
    }

}
