#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<std::vector<ASTNode *>, std::string> Parser::parseCallArguments(Program *program) {
        std::vector<ASTNode *> args;

        nextToken();

        if (peekTokenIs(tokens::RParen.type)) {
            return args;
        }

        tl::expected<ASTNode *, std::string> expectedExpression;

        expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedExpression) {
            return tl::unexpected{ std::move(expectedExpression).error() };
        }

        args.push_back(expectedExpression.value());

        while (peekTokenIs(tokens::Comma.type)) {
            nextToken();
            nextToken();

            expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

            if (not expectedExpression) {
                return tl::unexpected{ std::move(expectedExpression).error() };
            }

            args.push_back(expectedExpression.value());
        }

        if (auto expected = expectPeek(tokens::RParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return args;
    }

}
