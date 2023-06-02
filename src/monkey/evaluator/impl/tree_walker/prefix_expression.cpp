#include "evaluator/impl/tree_walker.hpp"

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalPrefixExpression(Scope *scope, std::string_view op, Object *obj) {
        if (op == "!") {
            return evalNotOperator(scope, obj);
        }
        else if (op == "not") {
            return evalNotOperator(scope, obj);
        }
        else if (op == "-") {
            return evalMinusOperator(scope, obj);
        }
        else {
            return tl::unexpected<std::string>{ "Unknown prefix operator" };
        }
    }

}
