#include "evaluator/impl/tree_walker.hpp"

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalInfixExpression(Scope *scope, std::string_view op, Object *lobj, Object *robj) {
        if (op == "+") {
            return evalSumExpression(scope, lobj, robj);
        }
        else if (op == "-") {
            return evalSubExpression(scope, lobj, robj);
        }
        else if (op == "*") {
            return evalMulExpression(scope, lobj, robj);
        }
        else if (op == "/") {
            return evalDivExpression(scope, lobj, robj);
        }
        else if (op == "%") {
            return evalModExpression(scope, lobj, robj);
        }
        else if (op == "<") {
            return evalLtExpression(scope, lobj, robj);
        }
        else if (op == ">") {
            return evalGtExpression(scope, lobj, robj);
        }
        else if (op == "==") {
            return evalEqExpression(scope, lobj, robj);
        }
        else if (op == "!=") {
            return evalNeExpression(scope, lobj, robj);
        }
        else {
            return tl::unexpected<std::string>{ "Unexpected operator" };
        }
    }

}
