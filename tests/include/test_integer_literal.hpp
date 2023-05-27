#pragma once

#include <string>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include "ast/ast.hpp"

namespace arti::monkey::testing {

    static tl::expected<void, std::string> testIntegerLiteral(ASTNode *node, int64_t value) {
        auto literal = dynamic_cast<IntegerLiteral *>(node);

        if (literal == nullptr) {
            return tl::unexpected<std::string>{ fmt::format("ASTNode not an 'IntegerLiteral', got: '{}'", node->token.type) };
        }

        if (literal->value != value) {
            return tl::unexpected<std::string>{ fmt::format("Expected IntegerLiteral with value '{}', got: '{}'", value, literal->value) };
        }

        if (literal->tokenLiteral() != fmt::to_string(value)) {
            return tl::unexpected<std::string>{ fmt::format("Expected IntegerLiteral with tokenLiteral '{}', got: '{}'", value, literal->value) };
        }

        return {};
    }

}
