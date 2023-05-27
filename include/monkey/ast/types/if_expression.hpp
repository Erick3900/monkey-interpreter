#pragma once

#include "ast/types/ast_node.hpp"
#include "ast/types/block_statement.hpp"

namespace arti::monkey {

    struct IfExpression : public ASTNode {
        ASTNode *condition;
        BlockStatement *consequence;
        BlockStatement *alternative;

        IfExpression();
        ~IfExpression() = default;

        IfExpression(IfExpression &&) = default;
        IfExpression(const IfExpression &) = default;

        IfExpression &operator=(IfExpression &&) = default;
        IfExpression &operator=(const IfExpression &) = default;

        std::string toString() const override;
    };

}
