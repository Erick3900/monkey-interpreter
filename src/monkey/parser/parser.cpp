#include "parser/parser.hpp"

#include <fmt/format.h>

#include "token/token_definitions.hpp"

namespace arti::monkey {

    static const std::unordered_map<Token_t, expressions::Precedence> precedences{
        { tokens::Eq.type, expressions::Precedence::EQUALS },
        { tokens::Ne.type, expressions::Precedence::EQUALS },

        { tokens::Lt.type, expressions::Precedence::LESS_GREATER },
        { tokens::Gt.type, expressions::Precedence::LESS_GREATER },

        { tokens::Plus.type , expressions::Precedence::SUM },
        { tokens::Minus.type, expressions::Precedence::SUM },

        { tokens::Slash.type   , expressions::Precedence::PRODUCT },
        { tokens::Asterisk.type, expressions::Precedence::PRODUCT },

        { tokens::LParen.type, expressions::Precedence::CALL },
    };

    Parser::Parser(std::unique_ptr<Lexer> lexer)
        : lexer(std::move(lexer))
        , currentToken{}
        , peekToken{} {
        if (not this->lexer) {
            throw std::runtime_error("Lexer provided to Parser is not valid");
        }

        nextToken();

        registerPrefix(tokens::Ident.type, std::bind_front(&Parser::parseIdentifier, this));
        registerPrefix(tokens::Int.type, std::bind_front(&Parser::parseIntegerLiteral, this));

        registerPrefix(tokens::Bang.type, std::bind_front(&Parser::parsePrefixExpression, this));
        registerPrefix(tokens::Minus.type, std::bind_front(&Parser::parsePrefixExpression, this));

        registerPrefix(tokens::True.type, std::bind_front(&Parser::parseBooleanLiteral, this));
        registerPrefix(tokens::False.type, std::bind_front(&Parser::parseBooleanLiteral, this));

        registerPrefix(tokens::LParen.type, std::bind_front(&Parser::parseGroupedExpression, this));

        registerPrefix(tokens::If.type, std::bind_front(&Parser::parseIfExpression, this));
        registerPrefix(tokens::Function.type, std::bind_front(&Parser::parseFunctionLiteral, this));

        registerInfix(tokens::Plus.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Minus.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::Slash.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Asterisk.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::Eq.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Ne.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::Lt.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Gt.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::LParen.type, std::bind_front(&Parser::parseCallExpression, this));
    }

    void Parser::registerInfix(Token_t tokenType, InfixParseFn fn) {
        infixParseFns[tokenType] = std::move(fn);
    }

    void Parser::registerPrefix(Token_t tokenType, PrefixParseFn fn) {
        prefixParseFns[tokenType] = std::move(fn);
    }

    void Parser::nextToken() {
        currentToken = lexer->currentToken();
        peekToken = lexer->nextToken();
    }

    tl::expected<std::unique_ptr<Program>, std::string> Parser::parseProgram() {
        auto program = std::make_unique<Program>();

        while (currentToken.type != tokens::EOF.type) {
            auto statementExp = parseStatement(program.get());

            if (statementExp.has_value()) {
                program->statements.push_back(statementExp.value());
            }
            else return tl::unexpected<std::string>{ statementExp.error() };

            nextToken();
        }

        return program;
    }

    expressions::Precedence Parser::peekPrecedence() {
        if (auto it = precedences.find(peekToken.type); it != precedences.end()) {
            return it->second;
        }

        return expressions::Precedence::LOWEST;
    }

    expressions::Precedence Parser::currentPrecedence() {
        if (auto it = precedences.find(currentToken.type); it != precedences.end()) {
            return it->second;
        }

        return expressions::Precedence::LOWEST;
    }

    tl::expected<void, std::string> Parser::expectPeek(Token_t tokenType) {
        if (auto expected = peekTokenIs(tokenType); not expected) {
            return expected;
        }

        nextToken();

        return {};
    }

    tl::expected<void, std::string> Parser::peekTokenIs(Token_t tokenType) {
        if (peekToken.type != tokenType) {
            return tl::unexpected<std::string>{ fmt::format("Expected next token to be '{}', got: '{}'", tokenType, peekToken.type) };
        }

        return {};
    }

    tl::expected<void, std::string> Parser::currentTokenIs(Token_t tokenType) {
        if (currentToken.type != tokenType) {
            return tl::unexpected<std::string>{ fmt::format("Expected token to be '{}', got: '{}'", tokenType, currentToken.type) };
        }

        return {};
    }
}
