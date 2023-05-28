#pragma once

#include <string>

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct StringLiteral : public ASTNode {
        std::string value;

        StringLiteral();
        ~StringLiteral() = default;

        StringLiteral(StringLiteral &&) = default;
        StringLiteral(const StringLiteral &) = default;

        StringLiteral &operator=(StringLiteral &&) = default;
        StringLiteral &operator=(const StringLiteral &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
