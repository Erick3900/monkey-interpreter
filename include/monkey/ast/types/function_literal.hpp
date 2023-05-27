#pragma once

#include <vector>

#include "ast/types/ast_node.hpp"
#include "ast/types/identifier.hpp"
#include "ast/types/block_statement.hpp"

namespace arti::monkey {

    struct FunctionLiteral : public ASTNode {
        std::vector<Identifier *> parameters;

        BlockStatement *statement;

        FunctionLiteral();
        ~FunctionLiteral() = default;

        FunctionLiteral(FunctionLiteral &&) = default;
        FunctionLiteral(const FunctionLiteral &) = default;

        FunctionLiteral &operator=(FunctionLiteral &&) = default;
        FunctionLiteral &operator=(const FunctionLiteral &) = default;

        std::string toString() const override;
    };

}
