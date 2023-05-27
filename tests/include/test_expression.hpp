#pragma once

#include <string>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include "ast/ast.hpp"

namespace arti::monkey::testing {

    static tl::expected<ASTNode *, std::string> testExpression(ASTNode *node) {
        auto expression = dynamic_cast<ExpressionStatement *>(node);

        if (expression == nullptr) {
            return tl::unexpected<std::string>{ fmt::format("ASTNode not an 'ExpressionStatement', got: '{}'", node->token.type) };
        }

        return expression->expression;
    }

}
