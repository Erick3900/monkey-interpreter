#include "evaluator/impl/tree_walker.hpp"

#include <iostream>

#include <fmt/format.h>

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::eval(Program *program, Scope *scope) {
        return evalProgram(scope, program->statements);
    }

    tl::expected<std::pair<Object *, std::unique_ptr<Scope>>, std::string> TreeWalkerEvaluator::eval(Program *program) {
        auto scope = std::make_unique<Scope>();
        auto expectedReturn = eval(program, scope.get());

        if (not expectedReturn) {
            return tl::unexpected{ std::move(expectedReturn).error() };
        }

        return std::pair{ expectedReturn.value(), std::move(scope) };
    }

    tl::expected<Object *, std::string> TreeWalkerEvaluator::eval(ASTNode *statement, Scope *scope) {
        if (auto nodeExpr = dynamic_cast<ExpressionStatement*>(statement); nodeExpr != nullptr) {
            return eval(nodeExpr->expression, scope);
        }

        if (auto nodeInt = dynamic_cast<IntegerLiteral *>(statement); nodeInt != nullptr) {
            auto obj = scope->newUnamed();
            obj->value = nodeInt->value;
            return obj;
        }

        if (auto nodeBool = dynamic_cast<BooleanLiteral *>(statement); nodeBool != nullptr) {
            auto obj = scope->newUnamed();
            obj->value = nodeBool->value;
            return obj;
        }

        if (auto nodeStr = dynamic_cast<StringLiteral *>(statement); nodeStr != nullptr) {
            auto obj = scope->newUnamed();
            obj->value = nodeStr->value;
            return obj;
        }

        if (auto nodePrefix = dynamic_cast<PrefixExpression *>(statement); nodePrefix != nullptr) {
            auto evalRightExpected = eval(nodePrefix->right, scope);

            if (not evalRightExpected) {
                return evalRightExpected;
            }

            return evalPrefixExpression(scope, nodePrefix->op, evalRightExpected.value());
        }

        if (auto nodeInfix = dynamic_cast<InfixExpression *>(statement); nodeInfix != nullptr) {
            auto evalLeftExpected = eval(nodeInfix->left, scope);

            if (not evalLeftExpected) {
                return evalLeftExpected;
            }

            auto evalRightExpected = eval(nodeInfix->right, scope);

            if (not evalLeftExpected) {
                return evalLeftExpected;
            }

            return evalInfixExpression(scope, nodeInfix->op, evalLeftExpected.value(), evalRightExpected.value());
        }

        if (auto nodeBlock = dynamic_cast<BlockStatement *>(statement); nodeBlock != nullptr) {
            return evalProgram(scope, nodeBlock->statements);
        }

        if (auto nodeIf = dynamic_cast<IfExpression *>(statement); nodeIf != nullptr) {
            return evalIfExpression(scope, statement);
        }

        if (auto nodeReturn = dynamic_cast<ReturnStatement *>(statement); nodeReturn != nullptr) {
            auto evalExpected = eval(nodeReturn->returnValue, scope);

            if (not evalExpected) {
                return evalExpected;
            }

            auto val = evalExpected.value();

            val->isReturn = true;

            return val;
        }

        if (auto nodeLet = dynamic_cast<LetStatement *>(statement); nodeLet != nullptr) {
            auto evalExpected = eval(nodeLet->value, scope);

            if (not evalExpected) {
                return evalExpected;
            }

            auto value = evalExpected.value();

            if (value->isUnnamed()) {
                auto nObj = value->takeOwnership();

                nObj->name = std::string{ nodeLet->name->value };

                std::string_view name = nObj->name;

                scope->set(name, std::move(nObj));

                return  scope->get(name);
            }
            else {
                auto nObj = scope->newObject(std::string{ nodeLet->name->value });

                nObj->value = value->value;

                return nObj;
            }
        }

        if (auto nodeIdent = dynamic_cast<Identifier *>(statement); nodeIdent != nullptr) {
            if (auto obj = scope->get(nodeIdent->value); obj != nullptr) {
                return obj;
            }

            return tl::unexpected<std::string>{ fmt::format("Identifier: {} not found", nodeIdent->value) };
        }

        return tl::unexpected<std::string>{ "Unsoported ASTNode type" };
    }

}
