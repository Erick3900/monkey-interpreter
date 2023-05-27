#include "ast/types/integer_litera.hpp"

#include <fmt/format.h>

namespace arti::monkey {

    IntegerLiteral::IntegerLiteral()
        : value(0) {}

    std::string IntegerLiteral::toString() const {
        return fmt::to_string(value);
    }

}
