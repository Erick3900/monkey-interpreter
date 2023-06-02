#pragma once

#include "evaluator/evaluator.hpp"

namespace arti::monkey {

    struct TreeWalkerEvaluator : public Evaluator {
        tl::expected<Object *, std::string> eval(Program *program, Scope *scope) override;
        tl::expected<std::pair<Object *, std::unique_ptr<Scope>>, std::string> eval(Program *program) override;

      private:
        tl::expected<Object *, std::string> eval(ASTNode *statement, Scope *scope);
        tl::expected<Object *, std::string> evalNotOperator(Scope *scope, Object *obj);
        tl::expected<Object *, std::string> evalMinusOperator(Scope *scope, Object *obj);
        tl::expected<Object *, std::string> evalPrefixExpression(Scope *scope, std::string_view op, Object *obj);
        tl::expected<Object *, std::string> evalInfixExpression(Scope *scope, std::string_view op, Object *lobj, Object *robj);

        tl::expected<Object *, std::string> evalSumExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalSubExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalMulExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalDivExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalModExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalGtExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalLtExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalEqExpression(Scope *scope, Object *lobj, Object *robj);
        tl::expected<Object *, std::string> evalNeExpression(Scope *scope, Object *lobj, Object *robj);

        tl::expected<Object *, std::string> evalIfExpression(Scope *scope, ASTNode *ie);
        tl::expected<Object *, std::string> evalProgram(Scope *scope, const std::vector<ASTNode *> &statements);

        tl::expected<Object *, std::string> evalBlockStatement(Scope *scope, ASTNode *bs);
    };

}
