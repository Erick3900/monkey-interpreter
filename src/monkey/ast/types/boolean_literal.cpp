#include "ast/types/boolean_literal.hpp"

#include <fmt/format.h>

namespace arti::monkey {

    BooleanLiteral::BooleanLiteral()
        : value{ false } { }

    std::string BooleanLiteral::toString() const {
        return fmt::to_string(value);
    }

}    // namespace arti::monkey
