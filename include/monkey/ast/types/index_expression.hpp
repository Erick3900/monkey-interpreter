#pragma once

#include <cstdint>

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct IndexExpression : public ASTNode {
        ASTNode *left;
        ASTNode *index;

        IndexExpression();
        ~IndexExpression() = default;

        IndexExpression(IndexExpression &&) = default;
        IndexExpression(const IndexExpression &) = default;

        IndexExpression &operator=(IndexExpression &&) = default;
        IndexExpression &operator=(const IndexExpression &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
