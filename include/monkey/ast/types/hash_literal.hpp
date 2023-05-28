#pragma once

#include <vector>

#include "ast/types/ast_node.hpp"
#include "ast/types/identifier.hpp"
#include "ast/types/block_statement.hpp"

namespace arti::monkey {

    struct HashLiteral : public ASTNode {
        std::vector<std::pair<ASTNode *, ASTNode *>> elements;

        HashLiteral();
        ~HashLiteral() = default;

        HashLiteral(HashLiteral &&) = default;
        HashLiteral(const HashLiteral &) = default;

        HashLiteral &operator=(HashLiteral &&) = default;
        HashLiteral &operator=(const HashLiteral &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
