#include "parser/parser.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseIdentifier(Program *program) {
        auto newIdentifier = program->newNode<Identifier>();
        newIdentifier->token = currentToken;
        newIdentifier->value = currentToken.literal;
        return newIdentifier;
    }

}
