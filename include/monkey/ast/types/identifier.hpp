#pragma once

#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct Identifier : public ASTNode {
        std::string_view value;

        std::string toString() const override;
        std::string dumpAst(std::string indentation, std::string_view indentStr) const override;
    };

}
