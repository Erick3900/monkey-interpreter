#include "ast/types/identifier.hpp"

#include <string>

#include <fmt/format.h>

namespace arti::monkey {

    std::string Identifier::toString() const {
        return std::string{ value };
    }

    std::string Identifier::dumpAst(std::string indentation, std::string_view indentStr) const {
        return fmt::format("{}Identifier {}", indentation, value);
    }

}    // namespace arti::monkey
