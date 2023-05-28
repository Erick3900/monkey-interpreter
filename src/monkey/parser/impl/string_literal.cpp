#include "parser/parser.hpp"

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseStringLiteral(Program *program) {
        auto newLiteral = program->newNode<StringLiteral>();
        newLiteral->token = currentToken;
        newLiteral->value = currentToken.literal.substr(1, currentToken.literal.size() - 2);
        return newLiteral;
    }

}
