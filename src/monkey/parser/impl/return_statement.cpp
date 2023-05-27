#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseReturnStatement(Program *program) {
        auto newStatement = program->newNode<ReturnStatement>();
        newStatement->token = currentToken;

        nextToken();

        auto expectedExpr = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedExpr) {
            return expectedExpr;
        }

        newStatement->returnValue = expectedExpr.value();

        if (peekTokenIs(tokens::Semicolon.type)) {
            nextToken();
        }

        return newStatement;
    }

}
