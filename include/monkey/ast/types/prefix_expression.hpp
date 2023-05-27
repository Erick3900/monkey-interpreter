#pragma once

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct PrefixExpression : public ASTNode {
        ASTNode *right;
        std::string_view op;

        PrefixExpression();
        ~PrefixExpression() = default;

        PrefixExpression(PrefixExpression &&) = default;
        PrefixExpression(const PrefixExpression &) = default;

        PrefixExpression &operator=(PrefixExpression &&) = default;
        PrefixExpression &operator=(const PrefixExpression &) = default;

        std::string toString() const override;
    };

}
