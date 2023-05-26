#pragma once

#include <vector>
#include <memory>

#include "token/token.hpp"
#include "ast/concepts.hpp"

namespace arti::monkey {

    struct ASTNode {
        virtual std::string_view tokenLiteral() const = 0;
        virtual std::string toString() const = 0;
    };

    struct Identifier : public ASTNode {
        Token token;
        std::string_view value;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct LetStatement : public ASTNode {
        Token token;

        Identifier *name;
        ASTNode *value; // Expression

        LetStatement();
        ~LetStatement() = default;

        LetStatement(LetStatement &&) = default;
        LetStatement(const LetStatement &) = default;

        LetStatement &operator=(LetStatement &&) = default;
        LetStatement &operator=(const LetStatement &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct ReturnStatement : public ASTNode {
        Token token;

        ASTNode *returnValue;

        ReturnStatement();
        ~ReturnStatement() = default;

        ReturnStatement(ReturnStatement &&) = default;
        ReturnStatement(const ReturnStatement &) = default;

        ReturnStatement &operator=(ReturnStatement &&) = default;
        ReturnStatement &operator=(const ReturnStatement &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct ExpressionStatement : public ASTNode {
        Token token;

        ASTNode *expression;

        ExpressionStatement();
        ~ExpressionStatement() = default;

        ExpressionStatement(ExpressionStatement &&) = default;
        ExpressionStatement(const ExpressionStatement &) = default;

        ExpressionStatement &operator=(ExpressionStatement &&) = default;
        ExpressionStatement &operator=(const ExpressionStatement &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct IntegerLiteral : public ASTNode {
        Token token;

        int64_t value;

        IntegerLiteral();
        ~IntegerLiteral() = default;

        IntegerLiteral(IntegerLiteral &&) = default;
        IntegerLiteral(const IntegerLiteral &) = default;

        IntegerLiteral &operator=(IntegerLiteral &&) = default;
        IntegerLiteral &operator=(const IntegerLiteral &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct PrefixExpression : public ASTNode {
        Token token;

        ASTNode *right;
        std::string_view op;

        PrefixExpression();
        ~PrefixExpression() = default;

        PrefixExpression(PrefixExpression &&) = default;
        PrefixExpression(const PrefixExpression &) = default;

        PrefixExpression &operator=(PrefixExpression &&) = default;
        PrefixExpression &operator=(const PrefixExpression &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct InfixExpression : public ASTNode {
        Token token;

        ASTNode *left;
        ASTNode *right;

        std::string_view op;

        InfixExpression();
        ~InfixExpression() = default;

        InfixExpression(InfixExpression &&) = default;
        InfixExpression(const InfixExpression &) = default;

        InfixExpression &operator=(InfixExpression &&) = default;
        InfixExpression &operator=(const InfixExpression &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct BooleanLiteral : public ASTNode {
        Token token;

        bool value;

        BooleanLiteral();
        ~BooleanLiteral() = default;

        BooleanLiteral(BooleanLiteral &&) = default;
        BooleanLiteral(const BooleanLiteral &) = default;

        BooleanLiteral &operator=(BooleanLiteral &&) = default;
        BooleanLiteral &operator=(const BooleanLiteral &) = default;

        std::string_view tokenLiteral() const override;
        std::string toString() const override;
    };

    struct Program {
        std::vector<std::unique_ptr<ASTNode>> astNodes;

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
