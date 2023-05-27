#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseIfExpression(Program *program) {
        auto newExpression = program->newNode<IfExpression>();
        newExpression->token = currentToken;

        if (auto expected = expectPeek(tokens::LParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        nextToken();

        auto expectedCondition = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedCondition) {
            return expectedCondition;
        }

        newExpression->condition = expectedCondition.value();

        if (auto expected = expectPeek(tokens::RParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        if (auto expected = expectPeek(tokens::LSquirly.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        auto expectedBlock = parseBlockStatement(program);

        if (not expectedBlock) {
            return expectedBlock;
        }

        newExpression->consequence = static_cast<BlockStatement *>(expectedBlock.value());

        if (peekTokenIs(tokens::Else.type)) {
            nextToken();

            if (auto expected = expectPeek(tokens::LSquirly.type); not expected) {
                return tl::unexpected{ std::move(expected).error() };
            }

            auto expectedElseBlock = parseBlockStatement(program);

            if (not expectedElseBlock) {
                return expectedElseBlock;
            }

            newExpression->alternative = static_cast<BlockStatement *>(expectedElseBlock.value());
        }

        return newExpression;
    }

}
