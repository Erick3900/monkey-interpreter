#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseInfixExpression(Program *program, ASTNode *left) {
        auto newExpression = program->newNode<InfixExpression>();
        newExpression->token = currentToken;
        newExpression->op = currentToken.literal;
        newExpression->left = left;

        auto precedence = currentPrecedence();

        nextToken();

        auto expressionExpected = parseExpression(program, precedence);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newExpression->right = expressionExpected.value();

        return newExpression;
    }

}
