#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseStatement(Program *program) {
        if (currentToken.type == tokens::Let.type) {
            return parseLetStatement(program);
        }
        else if (currentToken.type == tokens::Return.type) {
            return parseReturnStatement(program);
        }
        else {
         return parseExpressionStatement(program);
        }
    }

}
