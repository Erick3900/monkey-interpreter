#include "token/token.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    Token_t lookupIdent(std::string_view ident) {
        if (auto it = keywords.find(ident.data()); it != keywords.end()) {
            return it->second;
        }

        return tokens::Ident.type;
    }

}
