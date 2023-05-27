#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseCallExpression(Program *program, ASTNode *left) {
        auto newExpression = program->newNode<CallExpression>();
        newExpression->token = currentToken;
        newExpression->function = left;

        auto expectedArgs = parseCallArguments(program);

        if (not expectedArgs) {
            return tl::unexpected{ std::move(expectedArgs).error() };
        }

        newExpression->arguments = std::move(expectedArgs).value();

        return newExpression;
    }

}
