#pragma once

#include <string>
#include <string_view>

namespace arti::monkey {

    using Token_t = std::string;
    using Literal_t = std::string;

    struct Token {
        Token_t type;
        Literal_t literal;
    };

    Token_t lookupIdent(std::string_view ident);

}    // namespace arti::monkey
