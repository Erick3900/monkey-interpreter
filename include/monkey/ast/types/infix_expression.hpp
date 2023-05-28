#pragma once

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct InfixExpression : public ASTNode {
        ASTNode *left;
        ASTNode *right;

        std::string_view op;

        InfixExpression();
        ~InfixExpression() = default;

        InfixExpression(InfixExpression &&) = default;
        InfixExpression(const InfixExpression &) = default;

        InfixExpression &operator=(InfixExpression &&) = default;
        InfixExpression &operator=(const InfixExpression &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
