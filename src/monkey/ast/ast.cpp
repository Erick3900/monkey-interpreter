#include "ast/ast.hpp"

namespace arti::monkey {

    std::string_view Identifier::tokenLiteral() {
        return token.literal;
    }

    std::string_view LetStatement::tokenLiteral() {
        return token.literal;
    }

    std::string_view Program::tokenLiteral() {
        if (not statements.empty()) {
            return statements.front()->tokenLiteral();
        }

        return "";
    }

}    // namespace arti::monkey
