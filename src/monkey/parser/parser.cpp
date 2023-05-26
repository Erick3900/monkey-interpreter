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

        auto expressionExpected = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newStatement->expression = expressionExpected.value();

        if (peekTokenIs(tokens::Semicolon.type)) {
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
        auto newLiteral = program->newNode<IntegerLiteral>();
        newLiteral->token = currentToken;

        try {
            auto literal = std::stoll(currentToken.literal.data());
            newLiteral->value = literal;
        }
        catch(std::exception &err) {
            return tl::unexpected<std::string>{ fmt::format("Couldn't parse '{}' as an integer literal", currentToken.literal) };
        }

        return newLiteral;
    }

    tl::expected<ASTNode *, std::string> Parser::parseBooleanLiteral(Program *program) {
        auto newLiteral = program->newNode<BooleanLiteral>();
        newLiteral->token = currentToken;
        newLiteral->value = currentTokenIs(tokens::True.type).has_value();
        return newLiteral;
    }

    tl::expected<ASTNode *, std::string> Parser::parsePrefixExpression(Program *program) {
        auto newExpression = program->newNode<PrefixExpression>();
        newExpression->token = currentToken;
        newExpression->op = currentToken.literal;

        nextToken();

        auto expressionExpected = parseExpression(program, expressions::Precedence::PREFIX);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newExpression->right = expressionExpected.value();

        return newExpression;
    }

    tl::expected<ASTNode *, std::string> Parser::parseGroupedExpression(Program *program) {
        nextToken();

        auto expressionExpected = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expressionExpected) {
            return expressionExpected;
        }

        if (auto expected = expectPeek(tokens::RParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return expressionExpected.value();
    }

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

    tl::expected<ASTNode *, std::string> Parser::parseBlockStatement(Program *program) {
        auto newStatement = program->newNode<BlockStatement>();
        newStatement->token = currentToken;

        nextToken();

        while (not currentTokenIs(tokens::RSquirly.type) and not currentTokenIs(tokens::EOF.type)) {
            auto expectedStatement = parseStatement(program);

            if (not expectedStatement) {
                return expectedStatement;
            }

            newStatement->statements.push_back(expectedStatement.value());

            nextToken();
        }

        return newStatement;
    }

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

    tl::expected<ASTNode *, std::string> Parser::parseCallExpression(Program *program, ASTNode *left) {
        auto newExpression = program->newNode<CallExpression>();
        newExpression->token = currentToken;
        newExpression->function = left;

        auto expectedArgs = parseCallArguments(program);

        if (not expectedArgs) {
            return tl::unexpected{ std::move(expectedArgs).error() };
        }

        newExpression->arguments = std::move(expectedArgs).value();

        return newExpression;
    }

    tl::expected<std::vector<ASTNode *>, std::string> Parser::parseCallArguments(Program *program) {
        std::vector<ASTNode *> args;

        nextToken();

        if (peekTokenIs(tokens::RParen.type)) {
            return args;
        }

        tl::expected<ASTNode *, std::string> expectedExpression;

        expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

        if (not expectedExpression) {
            return tl::unexpected{ std::move(expectedExpression).error() };
        }

        args.push_back(expectedExpression.value());

        while (peekTokenIs(tokens::Comma.type)) {
            nextToken();
            nextToken();

            expectedExpression = parseExpression(program, expressions::Precedence::LOWEST);

            if (not expectedExpression) {
                return tl::unexpected{ std::move(expectedExpression).error() };
            }

            args.push_back(expectedExpression.value());
        }

        if (auto expected = expectPeek(tokens::RParen.type); not expected) {
            return tl::unexpected{ std::move(expected).error() };
        }

        return args;
    }

    tl::expected<ASTNode *, std::string> Parser::parseInfixExpression(Program *program, ASTNode *left) {
        auto newExpression = program->newNode<InfixExpression>();
        newExpression->token = currentToken;
        newExpression->op = currentToken.literal;
        newExpression->left = left;

        auto precedence = currentPrecedence();

        nextToken();

        auto expressionExpected = parseExpression(program, precedence);

        if (not expressionExpected) {
            return expressionExpected;
        }

        newExpression->right = expressionExpected.value();

        return newExpression;
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
