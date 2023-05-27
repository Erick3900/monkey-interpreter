#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseExpressionStatement(Program *program) {
        auto newStatement = program->newNode<ExpressionStatement>();
        newStatement->token = currentToken;

        auto expressionExpected = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newStatement->expression = expressionExpected.value();

        if (peekTokenIs(tokens::Semicolon.type)) {
            nextToken();
        }

        return newStatement;
    }

}
