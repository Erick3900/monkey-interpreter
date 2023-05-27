#pragma once

#include <list>
#include <vector>
#include <memory>

#include "ast/concepts.hpp"
#include "ast/types/ast_node.hpp"

namespace arti::monkey {

    struct Program {
        std::list<std::unique_ptr<ASTNode>> astNodes;

        std::vector<ASTNode *> statements;

        std::string toString() const;

        template <concepts::ASTNode NodeT, typename ...Args>
        [[nodiscard]] NodeT *newNode(Args &&...args) {
            auto node = std::make_unique<NodeT>(std::forward<Args>(args)...);

            if (node) {
                auto nodePtr = node.get();
                astNodes.emplace_back(std::move(node));
                return nodePtr;
            }

            return nullptr;
        }
    };

}
