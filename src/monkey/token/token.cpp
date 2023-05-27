#include "token/token.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    Token_t lookupIdent(Literal_t ident) {
        if (auto it = keywords.find(ident); it != keywords.end()) {
            return it->second;
        }

        return tokens::Ident.type;
    }

}
