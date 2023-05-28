#pragma once

#include <tl/expected.hpp>

#include "ast/ast.hpp"
#include "token/token.hpp"
#include "lexer/lexer.hpp"
#include "parser/precedence.hpp"

namespace arti::monkey {

    using PrefixParseFn = std::function<tl::expected<ASTNode *, std::string>(Program *)>;
    using InfixParseFn = std::function<tl::expected<ASTNode *, std::string>(Program *, ASTNode *)>;

    struct Parser {
        std::unique_ptr<Lexer> lexer;

        Token currentToken;
        Token peekToken;

        std::unordered_map<Token_t, InfixParseFn> infixParseFns;
        std::unordered_map<Token_t, PrefixParseFn> prefixParseFns;

        Parser(std::unique_ptr<Lexer> lexer);

        Parser() = delete;
        ~Parser() = default;

        Parser(Parser &&) = default;
        Parser(const Parser &) = delete;

        Parser &operator=(Parser &&) = default;
        Parser &operator=(const Parser &) = delete;

        tl::expected<std::unique_ptr<Program>, std::string> parseProgram();

        void registerInfix(Token_t tokenType, InfixParseFn fn);
        void registerPrefix(Token_t tokenType, PrefixParseFn fn);

      private:
        void nextToken();

        tl::expected<ASTNode *, std::string> parseStatement(Program *program);
        tl::expected<ASTNode *, std::string> parseLetStatement(Program *program);
        tl::expected<ASTNode *, std::string> parseConstStatement(Program *program);
        tl::expected<ASTNode *, std::string> parseReturnStatement(Program *program);
        tl::expected<ASTNode *, std::string> parseExpressionStatement(Program *program);
        tl::expected<ASTNode *, std::string> parseBlockStatement(Program *program);

        tl::expected<ASTNode *, std::string> parseIdentifier(Program *program);
        tl::expected<ASTNode *, std::string> parseIntegerLiteral(Program *program);
        tl::expected<ASTNode *, std::string> parseStringLiteral(Program *program);
        tl::expected<ASTNode *, std::string> parseBooleanLiteral(Program *program);
        tl::expected<ASTNode *, std::string> parseFunctionLiteral(Program *program);
        tl::expected<ASTNode *, std::string> parseArrayLiteral(Program *program);
        tl::expected<ASTNode *, std::string> parseHashLiteral(Program *program);

        tl::expected<ASTNode *, std::string> parseExpression(Program *program, expressions::Precedence precedence);

        tl::expected<ASTNode *, std::string> parseInfixExpression(Program *program, ASTNode *left);
        tl::expected<ASTNode *, std::string> parseIndexExpression(Program *program, ASTNode *left);
        tl::expected<ASTNode *, std::string> parseCallExpression(Program *program, ASTNode *left);
        tl::expected<ASTNode *, std::string> parsePrefixExpression(Program *program);
        tl::expected<ASTNode *, std::string> parseGroupedExpression(Program *program);
        tl::expected<ASTNode *, std::string> parseIfExpression(Program *program);

        tl::expected<std::vector<Identifier *>, std::string> parseFunctionParameters(Program *program);
        tl::expected<std::vector<ASTNode *>, std::string> parseCallArguments(Program *program);
        tl::expected<std::vector<ASTNode *>, std::string> parseExpressionList(Program *program);

        expressions::Precedence peekPrecedence();
        expressions::Precedence currentPrecedence();

        tl::expected<void, std::string> expectPeek(Token_t tokenType);
        tl::expected<void, std::string> peekTokenIs(Token_t tokenType);
        tl::expected<void, std::string> currentTokenIs(Token_t tokenType);
    };

}
