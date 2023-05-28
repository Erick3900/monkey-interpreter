#pragma once

#include <vector>

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct ArrayLiteral : public ASTNode {
        std::vector<ASTNode *> elements;

        ArrayLiteral();
        ~ArrayLiteral() = default;

        ArrayLiteral(ArrayLiteral &&) = default;
        ArrayLiteral(const ArrayLiteral &) = default;

        ArrayLiteral &operator=(ArrayLiteral &&) = default;
        ArrayLiteral &operator=(const ArrayLiteral &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
