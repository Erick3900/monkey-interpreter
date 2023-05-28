#pragma once

#include <vector>

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct CallExpression : public ASTNode {
        ASTNode *function;

        std::vector<ASTNode *> arguments;

        CallExpression();
        ~CallExpression() = default;

        CallExpression(CallExpression &&) = default;
        CallExpression(const CallExpression &) = default;

        CallExpression &operator=(CallExpression &&) = default;
        CallExpression &operator=(const CallExpression &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
