#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<ASTNode *, std::string> Parser::parseConstStatement(Program *program) {
        auto newStatement = program->newNode<ConstStatement>();
        newStatement->token = currentToken;

        if (auto expected = expectPeek(tokens::Ident.type); not expected) {
            return tl::unexpected<std::string>{ expected.error() };
        }

        newStatement->name = program->newNode<Identifier>();
        newStatement->name->token = currentToken;
        newStatement->name->value = currentToken.literal;

        if (auto expected = expectPeek(tokens::Assign.type); not expected) {
            return tl::unexpected<std::string>{ expected.error() };
        }

        nextToken();

        auto expectedValue = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedValue) {
            return expectedValue;
        }

        newStatement->value = expectedValue.value();

        if (peekTokenIs(tokens::Semicolon.type)) {
            nextToken();
        }

        return newStatement;
    }

}    // namespace arti::monkey
