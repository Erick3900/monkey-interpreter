#include "parser/parser.hpp"

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseExpression(Program *program, expressions::Precedence precedence) {
        auto prefixFn = prefixParseFns.find(currentToken.type);

        if (prefixFn == prefixParseFns.end()) {
            return tl::unexpected<std::string>{ fmt::format("Unknown expression type, no parser available for '{}'", currentToken.type) };
        }

        auto expectedExpr = prefixFn->second(program);

        if (not expectedExpr) {
            return expectedExpr;
        }

        auto leftExpr = expectedExpr.value();

        while (not peekTokenIs(tokens::Semicolon.type) && precedence < peekPrecedence()) {
            auto infixFn = infixParseFns.find(peekToken.type);

            if (infixFn == infixParseFns.end()) {
                return leftExpr;
            }

            nextToken();

            expectedExpr = infixFn->second(program, leftExpr);

            if (not expectedExpr) {
                return expectedExpr;
            }

            leftExpr = expectedExpr.value();
        }

        return leftExpr;
    }

}
