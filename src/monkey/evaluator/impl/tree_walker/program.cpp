#include "evaluator/impl/tree_walker.hpp"

#include "utils/overload_set.hpp"
#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalProgram(Scope *scope, const std::vector<ASTNode *> &statements) {
        Object *result = nullptr;

        for (auto statement : statements) {
            auto expectedResult = eval(statement, scope);

            if (not expectedResult) {
                return expectedResult;
            }

            result = expectedResult.value();

            if (result->isReturn) {
                return result;
            }
        }

        if (not result) {
            result = scope->newUnamed();
            result->value = Null_t{};
            return result;
        }

        return result;
    }

}
