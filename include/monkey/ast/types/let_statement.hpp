#pragma once

#include "ast/types/ast_node.hpp"
#include "ast/types/identifier.hpp"

namespace arti::monkey {

    struct LetStatement : public ASTNode {
        Identifier *name;
        ASTNode *value; // Expression

        LetStatement();
        ~LetStatement() = default;

        LetStatement(LetStatement &&) = default;
        LetStatement(const LetStatement &) = default;

        LetStatement &operator=(LetStatement &&) = default;
        LetStatement &operator=(const LetStatement &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
