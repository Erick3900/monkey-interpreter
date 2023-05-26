#pragma once

#include <list>
#include <vector>
#include <memory>

#include "token/token.hpp"
#include "ast/concepts.hpp"

namespace arti::monkey {

    struct ASTNode {
        Token token;

        virtual std::string toString() const = 0;
        virtual std::string_view tokenLiteral() const;
    };

    struct Identifier : public ASTNode {
        std::string_view value;

        std::string toString() const override;
    };

    struct LetStatement : public ASTNode {
        Identifier *name;
        ASTNode *value; // Expression

        LetStatement();
        ~LetStatement() = default;

        LetStatement(LetStatement &&) = default;
        LetStatement(const LetStatement &) = default;

        LetStatement &operator=(LetStatement &&) = default;
        LetStatement &operator=(const LetStatement &) = default;

        std::string toString() const override;
    };

    struct ReturnStatement : public ASTNode {
        ASTNode *returnValue;

        ReturnStatement();
        ~ReturnStatement() = default;

        ReturnStatement(ReturnStatement &&) = default;
        ReturnStatement(const ReturnStatement &) = default;

        ReturnStatement &operator=(ReturnStatement &&) = default;
        ReturnStatement &operator=(const ReturnStatement &) = default;

        std::string toString() const override;
    };

    struct ExpressionStatement : public ASTNode {
        ASTNode *expression;

        ExpressionStatement();
        ~ExpressionStatement() = default;

        ExpressionStatement(ExpressionStatement &&) = default;
        ExpressionStatement(const ExpressionStatement &) = default;

        ExpressionStatement &operator=(ExpressionStatement &&) = default;
        ExpressionStatement &operator=(const ExpressionStatement &) = default;

        std::string toString() const override;
    };

    struct IntegerLiteral : public ASTNode {
        int64_t value;

        IntegerLiteral();
        ~IntegerLiteral() = default;

        IntegerLiteral(IntegerLiteral &&) = default;
        IntegerLiteral(const IntegerLiteral &) = default;

        IntegerLiteral &operator=(IntegerLiteral &&) = default;
        IntegerLiteral &operator=(const IntegerLiteral &) = default;

        std::string toString() const override;
    };

    struct PrefixExpression : public ASTNode {
        ASTNode *right;
        std::string_view op;

        PrefixExpression();
        ~PrefixExpression() = default;

        PrefixExpression(PrefixExpression &&) = default;
        PrefixExpression(const PrefixExpression &) = default;

        PrefixExpression &operator=(PrefixExpression &&) = default;
        PrefixExpression &operator=(const PrefixExpression &) = default;

        std::string toString() const override;
    };

    struct InfixExpression : public ASTNode {
        ASTNode *left;
        ASTNode *right;

        std::string_view op;

        InfixExpression();
        ~InfixExpression() = default;

        InfixExpression(InfixExpression &&) = default;
        InfixExpression(const InfixExpression &) = default;

        InfixExpression &operator=(InfixExpression &&) = default;
        InfixExpression &operator=(const InfixExpression &) = default;

        std::string toString() const override;
    };

    struct BlockStatement : public ASTNode {
        std::vector<ASTNode *> statements;

        BlockStatement();
        ~BlockStatement() = default;

        BlockStatement(BlockStatement &&) = default;
        BlockStatement(const BlockStatement &) = default;

        BlockStatement &operator=(BlockStatement &&) = default;
        BlockStatement &operator=(const BlockStatement &) = default;

        std::string toString() const override;
    };

    struct IfExpression : public ASTNode {
        ASTNode *condition;
        BlockStatement *consequence;
        BlockStatement *alternative;

        IfExpression();
        ~IfExpression() = default;

        IfExpression(IfExpression &&) = default;
        IfExpression(const IfExpression &) = default;

        IfExpression &operator=(IfExpression &&) = default;
        IfExpression &operator=(const IfExpression &) = default;

        std::string toString() const override;
    };

    struct BooleanLiteral : public ASTNode {
        bool value;

        BooleanLiteral();
        ~BooleanLiteral() = default;

        BooleanLiteral(BooleanLiteral &&) = default;
        BooleanLiteral(const BooleanLiteral &) = default;

        BooleanLiteral &operator=(BooleanLiteral &&) = default;
        BooleanLiteral &operator=(const BooleanLiteral &) = default;

        std::string toString() const override;
    };

    struct FunctionLiteral : public ASTNode {
        std::vector<Identifier *> parameters;

        BlockStatement *statement;

        FunctionLiteral();
        ~FunctionLiteral() = default;

        FunctionLiteral(FunctionLiteral &&) = default;
        FunctionLiteral(const FunctionLiteral &) = default;

        FunctionLiteral &operator=(FunctionLiteral &&) = default;
        FunctionLiteral &operator=(const FunctionLiteral &) = default;

        std::string toString() const override;
    };

    struct CallExpression : public ASTNode {
        ASTNode *function;

        std::vector<ASTNode *> arguments;

        CallExpression();
        ~CallExpression() = default;

        CallExpression(CallExpression &&) = default;
        CallExpression(const CallExpression &) = default;

        CallExpression &operator=(CallExpression &&) = default;
        CallExpression &operator=(const CallExpression &) = default;

        std::string toString() const override;
    };

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
