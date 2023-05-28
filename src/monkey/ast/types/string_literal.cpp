#include "ast/types/string_literal.hpp"

#include <fmt/format.h>

namespace arti::monkey {

    StringLiteral::StringLiteral()
        : value{} {}

    std::string StringLiteral::toString() const {
        return token.literal.data();
    }

    std::string StringLiteral::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format("{}String '{}'", indentation, value);
    }

}
