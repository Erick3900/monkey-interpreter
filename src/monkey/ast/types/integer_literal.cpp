#include "ast/types/integer_literal.hpp"

#include <fmt/format.h>

namespace arti::monkey {

    IntegerLiteral::IntegerLiteral()
        : value(0) {}

    std::string IntegerLiteral::toString() const {
        return fmt::to_string(value);
    }

    std::string IntegerLiteral::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format("{}Integer {}", indentation, value);
    }

}
