#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    std::string_view ASTNode::tokenLiteral() const {
        return token.literal;
    }

}    // namespace arti::monkey
