#include "ast/types/boolean_literal.hpp"

#include <sstream>

#include <fmt/format.h>

namespace arti::monkey {

    BooleanLiteral::BooleanLiteral()
        : value{ false } { }

    std::string BooleanLiteral::toString() const {
        return fmt::to_string(value);
    }

    std::string BooleanLiteral::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format("{}BooleanLiteral {}", indentation, value);
    }

}    // namespace arti::monkey
