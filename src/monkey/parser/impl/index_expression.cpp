#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseIndexExpression(Program *program, ASTNode *left) {
        auto newExpression = program->newNode<IndexExpression>();
        newExpression->token = currentToken;
        newExpression->left = left;

        nextToken();

        auto expressionExpected = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newExpression->index = expressionExpected.value();
        if (auto expected = expectPeek(tokens::RBracket.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return newExpression;
    }

}
