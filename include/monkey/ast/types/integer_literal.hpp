#pragma once

#include <cstdint>

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct IntegerLiteral : public ASTNode {
        int64_t value;

        IntegerLiteral();
        ~IntegerLiteral() = default;

        IntegerLiteral(IntegerLiteral &&) = default;
        IntegerLiteral(const IntegerLiteral &) = default;

        IntegerLiteral &operator=(IntegerLiteral &&) = default;
        IntegerLiteral &operator=(const IntegerLiteral &) = default;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
