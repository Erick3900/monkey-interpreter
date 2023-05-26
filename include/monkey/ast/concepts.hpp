#pragma once

#include <concepts>
#include <string_view>

namespace arti::monkey {
    
    struct ASTNode;

    namespace concepts {

        template <typename NodeT>
        concept ASTNode = requires(NodeT t) {
            { t.tokenLiteral() } -> std::convertible_to<std::string_view>;
            requires std::is_base_of<ASTNode, NodeT>::value;
        };

    }    // namespace concepts
//
}    // namespace arti::monkey
