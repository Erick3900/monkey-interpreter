#include "parser/parser.hpp"

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
        
        registerInfix(tokens::Plus.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Minus.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::Slash.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Asterisk.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::Eq.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Ne.type, std::bind_front(&Parser::parseInfixExpression, this));

        registerInfix(tokens::Lt.type, std::bind_front(&Parser::parseInfixExpression, this));
        registerInfix(tokens::Gt.type, std::bind_front(&Parser::parseInfixExpression, this));
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
            auto statement_exp = parseStatement(program.get());

            if (statement_exp.has_value()) {
                program->statements.push_back(statement_exp.value());
            }
            else return tl::unexpected<std::string>{ statement_exp.error() };

            nextToken();
        }

        return program;
    }

    tl::expected<ASTNode *, std::string> Parser::parseStatement(Program *program) {
        if (currentToken.type == tokens::Let.type) {
            return parseLetStatement(program);
        }
        else if (currentToken.type == tokens::Return.type) {
            return parseReturnStatement(program);
        }
        else {
         return parseExpressionStatement(program);
        }
    }

    tl::expected<ASTNode *, std::string> Parser::parseLetStatement(Program *program) {
        auto newStatement = program->newNode<LetStatement>();
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

    tl::expected<ASTNode *, std::string> Parser::parseReturnStatement(Program *program) {
        auto newStatement = program->newNode<ReturnStatement>();
        newStatement->token = currentToken;

        nextToken();

        auto expectedExpr = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedExpr) {
            return expectedExpr;
        }

        newStatement->returnValue = expectedExpr.value();

        if (peekTokenIs(tokens::Semicolon.type)) {
            nextToken();
        }

        return newStatement;
    }

    tl::expected<ASTNode *, std::string> Parser::parseExpressionStatement(Program *program) {
        auto newStatement = program->newNode<ExpressionStatement>();
        newStatement->token = currentToken;

        auto expression_expected = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expression_expected) {
            return expression_expected;
        }

        newStatement->expression = expression_expected.value();

        if (auto expected = peekTokenIs(tokens::Semicolon.type); expected) {
            nextToken();
        }

        return newStatement;
    }

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
    
    tl::expected<ASTNode *, std::string> Parser::parseIdentifier(Program *program) {
        auto newIdentifier = program->newNode<Identifier>();
        newIdentifier->token = currentToken;
        newIdentifier->value = currentToken.literal;
        return newIdentifier;
    }

    tl::expected<ASTNode *, std::string> Parser::parseIntegerLiteral(Program *program) {
        auto newIdentifier = program->newNode<IntegerLiteral>();
        newIdentifier->token = currentToken;

        try {
            auto literal = std::stoll(currentToken.literal.data());
            newIdentifier->value = literal;
        }
        catch(std::exception &err) {
            return tl::unexpected<std::string>{ fmt::format("Couldn't parse '{}' as an integer literal", currentToken.literal) };
        }

        return newIdentifier;
    }

    tl::expected<ASTNode *, std::string> Parser::parseBooleanLiteral(Program *program) {
        auto newIdentifier = program->newNode<BooleanLiteral>();
        newIdentifier->token = currentToken;
        newIdentifier->value = currentTokenIs(tokens::True.type).has_value();
        return newIdentifier;
    }

    tl::expected<ASTNode *, std::string> Parser::parsePrefixExpression(Program *program) {
        auto newIdentifier = program->newNode<PrefixExpression>();
        newIdentifier->token = currentToken;
        newIdentifier->op = currentToken.literal;

        nextToken();

        auto expression_expected = parseExpression(program, expressions::Precedence::PREFIX);

        if (not expression_expected) {
            return expression_expected;
        }

        newIdentifier->right = expression_expected.value();

        return newIdentifier;
    }

    tl::expected<ASTNode *, std::string> Parser::parseInfixExpression(Program *program, ASTNode *left) {
        auto newIdentifier = program->newNode<InfixExpression>();
        newIdentifier->token = currentToken;
        newIdentifier->op = currentToken.literal;
        newIdentifier->left = left;

        auto precedence = currentPrecedence();

        nextToken();

        auto expression_expected = parseExpression(program, precedence);

        if (not expression_expected) {
            return expression_expected;
        }

        newIdentifier->right = expression_expected.value();

        return newIdentifier;
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
