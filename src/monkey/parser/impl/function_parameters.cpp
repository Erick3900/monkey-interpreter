#include "parser/parser.hpp"

#include "token/token_definitions.hpp"

namespace arti::monkey {

    tl::expected<std::vector<Identifier *>, std::string> Parser::parseFunctionParameters(Program *program) {
        std::vector<Identifier *> identifiers;

        if (peekTokenIs(tokens::RParen.type)) {
            nextToken();
            return identifiers;
        }

        nextToken();

        identifiers.push_back(static_cast<Identifier *>(parseIdentifier(program).value()));

        while (peekTokenIs(tokens::Comma.type)) {
            nextToken();
            nextToken();

            identifiers.push_back(static_cast<Identifier *>(parseIdentifier(program).value()));
        }

        if (auto expected = expectPeek(tokens::RParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return identifiers;
    }

}
