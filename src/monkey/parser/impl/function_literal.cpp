#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseFunctionLiteral(Program *program) {
        auto newLiteral = program->newNode<FunctionLiteral>();
        newLiteral->token = currentToken;

        if (auto expected = expectPeek(tokens::LParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        auto expectedParameter = parseFunctionParameters(program);

        if (not expectedParameter) {
            return tl::unexpected<std::string>{ std::move(expectedParameter).error() };
        }

        newLiteral->parameters = std::move(expectedParameter).value();

        if (auto expected = expectPeek(tokens::LSquirly.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        } 

        auto expectedBlock = parseBlockStatement(program);

        if (not expectedBlock) {
            return expectedBlock;
        }

        newLiteral->statement = static_cast<BlockStatement *>(expectedBlock.value());

        return newLiteral;
    }

}
