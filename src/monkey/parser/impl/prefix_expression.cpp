#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parsePrefixExpression(Program *program) {
        auto newExpression = program->newNode<PrefixExpression>();
        newExpression->token = currentToken;
        newExpression->op = currentToken.literal;

        nextToken();

        auto expressionExpected = parseExpression(program, expressions::Precedence::PREFIX);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newExpression->right = expressionExpected.value();

        return newExpression;
    }

}
