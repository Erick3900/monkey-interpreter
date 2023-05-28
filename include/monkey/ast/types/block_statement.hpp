#pragma once

#include <vector>

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct BlockStatement : public ASTNode {
        std::vector<ASTNode *> statements;

        BlockStatement();
        ~BlockStatement() = default;

        BlockStatement(BlockStatement &&) = default;
        BlockStatement(const BlockStatement &) = default;

        BlockStatement &operator=(BlockStatement &&) = default;
        BlockStatement &operator=(const BlockStatement &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
