#pragma once

#include <vector>
#include <memory>

#include "token/token.hpp"
#include "ast/concepts.hpp"

namespace arti::monkey {

    struct ASTNode {
        virtual std::string_view tokenLiteral() = 0;
    };

    struct Identifier : public ASTNode {
        Token token;
        std::string_view value;

        std::string_view tokenLiteral() override;
    };

    struct LetStatement : public ASTNode {
        Token token;

        Identifier *name;
        ASTNode *value; // Expression

        std::string_view tokenLiteral() override;
    };

    struct Program {
        std::vector<std::unique_ptr<ASTNode>> astNodes;

        std::vector<ASTNode *> statements;

        template <concepts::ASTNode NodeT, typename ...Args>
        NodeT *newNode(Args &&...args) {
            auto node = std::make_unique<NodeT>(std::forward<Args>(args)...);

            if (node) {
                astNodes.emplace_back(std::move(node));
                return astNodes.back().get();
            }

            return nullptr;
        }

        std::string_view tokenLiteral();
    };

}
