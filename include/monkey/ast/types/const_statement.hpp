#pragma once

#include "ast/types/ast_node.hpp"
#include "ast/types/identifier.hpp"

namespace arti::monkey {

    struct ConstStatement : public ASTNode {
        Identifier *name;
        ASTNode *value; // Expression

        ConstStatement();
        ~ConstStatement() = default;

        ConstStatement(ConstStatement &&) = default;
        ConstStatement(const ConstStatement &) = default;

        ConstStatement &operator=(ConstStatement &&) = default;
        ConstStatement &operator=(const ConstStatement &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
