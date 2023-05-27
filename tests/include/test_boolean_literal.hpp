#pragma once

#include <string>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include "ast/ast.hpp"

namespace arti::monkey::testing {

    static tl::expected<void, std::string> testBooleanLiteral(ASTNode *node, bool value) {
        auto literal = dynamic_cast<BooleanLiteral *>(node);

        if (literal == nullptr) {
            return tl::unexpected<std::string>{ fmt::format("ASTNode not an 'BooleanLiteral', got: '{}'", node->token.type) };
        }

        if (literal->value != value) {
            return tl::unexpected<std::string>{ fmt::format("Expected BooleanLiteral with value '{}', got: '{}'", value, literal->value) };
        }

        if (literal->tokenLiteral() != fmt::to_string(value)) {
            return tl::unexpected<std::string>{ fmt::format("Expected BooleanLiteral with tokenLiteral '{}', got: '{}'", value, literal->value) };
        }

        return {};
    }

}
