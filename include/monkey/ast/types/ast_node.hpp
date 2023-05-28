#pragma once

#include "token/token.hpp"

namespace arti::monkey {

    struct ASTNode {
        Token token;

        virtual std::string toString() const = 0;
        virtual std::string_view tokenLiteral() const;
        virtual std::string dumpAst(std::string indentation, std::string_view indentStr) const = 0;
    };

}
