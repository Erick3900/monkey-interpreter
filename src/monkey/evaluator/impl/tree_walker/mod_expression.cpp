#include "evaluator/impl/tree_walker.hpp"

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalModExpression(Scope *scope, Object *lobj, Object *robj) {
        if (std::holds_alternative<int64_t>(lobj->value) and std::holds_alternative<int64_t>(robj->value)) {
            if (lobj->isUnnamed()) {
                lobj->value = std::get<int64_t>(lobj->value) % std::get<int64_t>(robj->value);
                if (robj->isUnnamed()) {
                    auto drop = robj->takeOwnership();
                }
                return lobj;
            }
            else if (robj->isUnnamed()) {
                robj->value = std::get<int64_t>(robj->value) % std::get<int64_t>(lobj->value);
                if (lobj->isUnnamed()) {
                    auto drop = lobj->takeOwnership();
                }
                return robj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<int64_t>(lobj->value) % std::get<int64_t>(robj->value);
                return nObj;
            }
        }
        else {
            return tl::unexpected<std::string>{ "Invalid types for / operation" };
        }
    }

}
