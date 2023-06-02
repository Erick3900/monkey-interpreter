#include "evaluator/impl/tree_walker.hpp"

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalEqExpression(Scope *scope, Object *lobj, Object *robj) {
        if (std::holds_alternative<int64_t>(lobj->value) and std::holds_alternative<int64_t>(robj->value)) {
            if (lobj->isUnnamed()) {
                lobj->value = std::get<int64_t>(lobj->value) == std::get<int64_t>(robj->value);
                if (robj->isUnnamed()) {
                    auto drop = robj->takeOwnership();
                }
                return lobj;
            }
            else if (robj->isUnnamed()) {
                robj->value = std::get<int64_t>(robj->value) == std::get<int64_t>(lobj->value);
                if (lobj->isUnnamed()) {
                    auto drop = lobj->takeOwnership();
                }
                return robj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<int64_t>(lobj->value) == std::get<int64_t>(robj->value);
                return nObj;
            }
        }
        else if (std::holds_alternative<int64_t>(lobj->value) and std::holds_alternative<bool>(robj->value)) {
            if (lobj->isUnnamed()) {
                lobj->value = std::get<int64_t>(lobj->value) == std::get<bool>(robj->value);
                if (robj->isUnnamed()) {
                    auto drop = robj->takeOwnership();
                }
                return lobj;
            }
            else if (robj->isUnnamed()) {
                robj->value = std::get<int64_t>(robj->value) == std::get<bool>(lobj->value);
                if (lobj->isUnnamed()) {
                    auto drop = lobj->takeOwnership();
                }
                return robj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<int64_t>(lobj->value) == std::get<bool>(robj->value);
                return nObj;
            }
        }
        else if (std::holds_alternative<bool>(lobj->value) and std::holds_alternative<int64_t>(robj->value)) {
            if (lobj->isUnnamed()) {
                lobj->value = std::get<bool>(lobj->value) == std::get<int64_t>(robj->value);
                if (robj->isUnnamed()) {
                    auto drop = robj->takeOwnership();
                }
                return lobj;
            }
            else if (robj->isUnnamed()) {
                robj->value = std::get<bool>(robj->value) == std::get<int64_t>(lobj->value);
                if (lobj->isUnnamed()) {
                    auto drop = lobj->takeOwnership();
                }
                return robj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<bool>(lobj->value) == std::get<int64_t>(robj->value);
                return nObj;
            }
        }
        else if (std::holds_alternative<bool>(lobj->value) and std::holds_alternative<bool>(robj->value)) {
            if (lobj->isUnnamed()) {
                lobj->value = std::get<bool>(lobj->value) == std::get<bool>(robj->value);
                if (robj->isUnnamed()) {
                    auto drop = robj->takeOwnership();
                }
                return lobj;
            }
            else if (robj->isUnnamed()) {
                robj->value = std::get<bool>(robj->value) == std::get<bool>(lobj->value);
                if (lobj->isUnnamed()) {
                    auto drop = lobj->takeOwnership();
                }
                return robj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<bool>(lobj->value) == std::get<bool>(robj->value);
                return nObj;
            }
        }
        else if (std::holds_alternative<std::string>(lobj->value) and std::holds_alternative<std::string>(robj->value)) {
            if (lobj->isUnnamed()) {
                lobj->value = std::get<std::string>(lobj->value) == std::get<std::string>(robj->value);
                if (robj->isUnnamed()) {
                    auto drop = robj->takeOwnership();
                }
                return lobj;
            }
            else if (robj->isUnnamed()) {
                robj->value = std::get<std::string>(robj->value) == std::get<std::string>(lobj->value);
                if (lobj->isUnnamed()) {
                    auto drop = lobj->takeOwnership();
                }
                return robj;
            }
            else {
                auto nObj = scope->newUnamed();
                nObj->value = std::get<std::string>(lobj->value) == std::get<std::string>(robj->value);
                return nObj;
            }
        }
        else {
            return tl::unexpected<std::string>{ "Invalid types for == operation" };
        }
    }

}
