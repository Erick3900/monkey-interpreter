#include "evaluator/impl/tree_walker.hpp"

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalMinusOperator(Scope *scope, Object *obj) {
        if (std::holds_alternative<int64_t>(obj->value)) {
            if (obj->isUnnamed()) {
                obj->value = -std::get<int64_t>(obj->value);
                return obj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = -std::get<int64_t>(obj->value);
                return nObj;
            }
        }
        else if (std::holds_alternative<bool>(obj->value)) {
            if (obj->isUnnamed()) {
                obj->value = std::get<bool>(obj->value) ? -1 : 0;
                return obj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<bool>(obj->value) ? -1 : 0;
                return nObj;
            }
        }
        else {
            return tl::unexpected<std::string>{ "Invalid right expression for not operator" };
        }
    }

}
