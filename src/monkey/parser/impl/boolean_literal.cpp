#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseBooleanLiteral(Program *program) {
        auto newLiteral = program->newNode<BooleanLiteral>();
        newLiteral->token = currentToken;
        newLiteral->value = currentTokenIs(tokens::True.type).has_value();
        return newLiteral;
    }

}
