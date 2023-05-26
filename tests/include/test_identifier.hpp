#pragma once

#include <string>

#include <tl/expected.hpp>

#include "ast/ast.hpp"

namespace arti::monkey::testing {

    static tl::expected<void, std::string> testIdentifier(ASTNode *node, std::string_view value) {
    auto identifier = dynamic_cast<Identifier *>(node);

        if (identifier == nullptr) {
            return tl::unexpected<std::string>{ fmt::format("ASTNode not an 'Identifier', got: '{}'", node->token.type) };
        }

        if (identifier->value != value) {
            return tl::unexpected<std::string>{ fmt::format("Expected Identifier with value '{}', got: '{}'", value, identifier->value) };
        }

        if (identifier->tokenLiteral() != value) {
            return tl::unexpected<std::string>{ fmt::format("Expected Identifier with tokenLiteral '{}', got: '{}'", value, identifier->value) };
        }

        return {};
    }

}
