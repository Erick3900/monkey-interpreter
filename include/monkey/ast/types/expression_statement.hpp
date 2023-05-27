#pragma once

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct ExpressionStatement : public ASTNode {
        ASTNode *expression;

        ExpressionStatement();
        ~ExpressionStatement() = default;

        ExpressionStatement(ExpressionStatement &&) = default;
        ExpressionStatement(const ExpressionStatement &) = default;

        ExpressionStatement &operator=(ExpressionStatement &&) = default;
        ExpressionStatement &operator=(const ExpressionStatement &) = default;

        std::string toString() const override;
    };

}
