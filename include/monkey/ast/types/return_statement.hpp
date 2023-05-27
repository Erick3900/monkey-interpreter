#pragma once

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct ReturnStatement : public ASTNode {
        ASTNode *returnValue;

        ReturnStatement();
        ~ReturnStatement() = default;

        ReturnStatement(ReturnStatement &&) = default;
        ReturnStatement(const ReturnStatement &) = default;

        ReturnStatement &operator=(ReturnStatement &&) = default;
        ReturnStatement &operator=(const ReturnStatement &) = default;

        std::string toString() const override;
    };

}
