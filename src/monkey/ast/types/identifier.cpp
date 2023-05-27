#include "ast/types/identifier.hpp"

#include <string>

namespace arti::monkey {

    std::string Identifier::toString() const {
        return std::string{ value };
    }

}    // namespace arti::monkey
