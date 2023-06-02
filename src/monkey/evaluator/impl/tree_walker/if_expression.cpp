#include "evaluator/impl/tree_walker.hpp"

#include "utils/overload_set.hpp"
#include "ast/ast.hpp"

namespace arti::monkey {

    bool isTruthy(const Object::Value_t &value) {
        using namespace arti::monkey;

        return std::visit(
            nstd::OverloadSet{
                [&](Null_t) -> bool {
                    return false;
                },
                [&](bool value) -> bool {
                    return value;
                },
                [&](int64_t value) -> bool {
                    return value != 0;
                },
                [&](const std::string &value) -> bool {
                    return not value.empty();
                },
            },
            value
        );
    }

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalIfExpression(Scope *scope, ASTNode *ie) {
        auto node = static_cast<IfExpression *>(ie);

        auto conditionExpected = eval(node->condition, scope);

        if (not conditionExpected) {
            return conditionExpected;
        }

        auto value = conditionExpected.value();

        if (isTruthy(value->value)) {
            return eval(node->consequence, scope);
        }
        else {
            if (node->alternative != nullptr) {
                return eval(node->alternative, scope);
            }

            auto obj = scope->newUnamed();
            obj->value = Null_t{};
            return obj;
        }
    }

}
