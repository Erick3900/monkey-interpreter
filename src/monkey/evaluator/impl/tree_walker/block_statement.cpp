#include "evaluator/impl/tree_walker.hpp"

#include "ast/ast.hpp"

namespace arti::monkey {

    tl::expected<Object *, std::string> TreeWalkerEvaluator::evalBlockStatement(Scope *scope, ASTNode *bs) {
        BlockStatement *node = static_cast<BlockStatement *>(bs);
        Object *result = nullptr;

        for (auto statement : node->statements) {
            auto expectedResult = eval(statement, scope);

            if (not expectedResult) {
                return expectedResult;
            }

            result = expectedResult.value();

            if (result and result->isReturn) {
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
