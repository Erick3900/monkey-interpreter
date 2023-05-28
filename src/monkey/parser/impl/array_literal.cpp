#include "parser/parser.hpp"

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseArrayLiteral(Program *program) {
        auto newLiteral = program->newNode<ArrayLiteral>();
        newLiteral->token = currentToken;

        auto expectedList = parseExpressionList(program);

        if (not expectedList) {
            return tl::unexpected{ std::move(expectedList).error() };
        }

        newLiteral->elements = std::move(expectedList).value();

        return newLiteral;
    }

}    // namespace arti::monkey
