#pragma once

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct BooleanLiteral : public ASTNode {
        bool value;

        BooleanLiteral();
        ~BooleanLiteral() = default;

        BooleanLiteral(BooleanLiteral &&) = default;
        BooleanLiteral(const BooleanLiteral &) = default;

        BooleanLiteral &operator=(BooleanLiteral &&) = default;
        BooleanLiteral &operator=(const BooleanLiteral &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
