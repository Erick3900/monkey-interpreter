#include "parser/parser.hpp"

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseIntegerLiteral(Program *program) {
        auto newLiteral = program->newNode<IntegerLiteral>();
        newLiteral->token = currentToken;

        try {
            auto literal = std::stoll(currentToken.literal.data());
            newLiteral->value = literal;
        }
        catch(std::exception &err) {
            return tl::unexpected<std::string>{ fmt::format("Couldn't parse '{}' as an integer literal", currentToken.literal) };
        }

        return newLiteral;
    }

}
