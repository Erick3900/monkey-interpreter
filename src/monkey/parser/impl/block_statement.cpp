#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseBlockStatement(Program *program) {
        auto newStatement = program->newNode<BlockStatement>();
        newStatement->token = currentToken;

        nextToken();

        while (not currentTokenIs(tokens::RSquirly.type) and not currentTokenIs(tokens::EOF.type)) {
            auto expectedStatement = parseStatement(program);

            if (not expectedStatement) {
                return expectedStatement;
            }

            newStatement->statements.push_back(expectedStatement.value());

            nextToken();
        }

        return newStatement;
    }

}
