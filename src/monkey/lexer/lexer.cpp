#include "lexer/lexer.hpp"

#include <iostream>

#include <fmt/format.h>

#include "utils/strings.hpp"
#include "token/token_definitions.hpp"

namespace arti::monkey {

    static constexpr std::string_view readIdentifier(std::string_view line) {
        auto iter = line.begin();

        while (iter != line.end() && str::isLetter(*iter)) {
            ++iter;
        }

        return { line.begin(), iter };
    }

    static constexpr std::string_view readNumber(std::string_view line) {
        auto iter = line.begin();

        while (iter != line.end() && str::isDigit(*iter)) {
            ++iter;
        }

        return { line.begin(), iter };
    }

    static constexpr std::string_view readString(std::string_view line) {
        auto iter = line.begin();
        ++iter;

        while (iter != line.end() && *iter != '"') {
            if (*iter == '\\') {
                ++iter;
                if (iter != line.end()) {
                    ++iter;
                }
            }
            else ++iter;
        }

        return { line.begin(), iter + 1 };
    }

    static constexpr void skipWhitespace(std::string::iterator &iter, const std::string &line) {
        while (iter != line.end() && str::isWhitespace(*iter)) {
            ++iter;
        }
    };

    static constexpr char peek(std::string::iterator &iter, const std::string &line) {
        if (iter == line.end() || (iter + 1) == line.end()) {
            return 0;
        }

        return *(iter + 1);
    };

    Lexer::Lexer(std::filesystem::path sourcePath)
        : lineCount(0)
        , position(0)
        , sourceCode()
        , sourcePath(sourcePath)
        , sourceStream(nullptr) {
        auto stream = std::make_unique<std::ifstream>(sourcePath);

        if (not stream->is_open()) {
            throw std::runtime_error(fmt::format("Couldn't open file '{}'", sourcePath.string()));
        }

        sourceStream = std::move(stream);

        tokensGenerator = init();
    }

    Lexer::Lexer(std::unique_ptr<std::istream> sourceStream)
        : lineCount(0)
        , position(0)
        , sourceCode()
        , sourcePath("stream")
        , sourceStream(std::move(sourceStream)) {
        tokensGenerator = init();
    }

    void Lexer::forward() {
        if (tokensIterator.handle == nullptr) {
            tokensIterator = begin();
        }
        else {
            ++tokensIterator;
        }
    }

    Token Lexer::nextToken() {
        if (tokensIterator.handle == nullptr) {
            tokensIterator = begin();
            return *tokensIterator;
        }

        ++tokensIterator;
        return *tokensIterator;
    }

    Token Lexer::currentToken() {
        if (tokensIterator.handle == nullptr) {
            tokensIterator = begin();
        }

        return *tokensIterator;
    }

    Lexer::iterator Lexer::begin() {
        return tokensGenerator.begin();
    }

    Lexer::iterator_sentinel Lexer::end() {
        return tokensGenerator.end();
    }

    nstd::generator<Token> Lexer::init() {
        Token tok;
        std::string line;

        while (std::getline(*sourceStream, line)) {
            sourceCode.append(line);
            sourceCode.append("\n");
        }

        auto iter = sourceCode.begin();

        while (iter != sourceCode.end()) {
            skipWhitespace(iter, sourceCode);

            if (iter == sourceCode.end()) {
                break;
            }

            switch(*iter) {
                case '<': tok = tokens::Lt; break;
                case '>': tok = tokens::Gt; break;
                case '.': tok = tokens::Dot; break;
                case '%': tok = tokens::Mod; break;
                case '+': tok = tokens::Plus; break;
                case '-': tok = tokens::Minus; break;
                case ',': tok = tokens::Comma; break;
                case '/': tok = tokens::Slash; break;
                case ':': tok = tokens::Colon; break;
                case '(': tok = tokens::LParen; break;
                case ')': tok = tokens::RParen; break;
                case '*': tok = tokens::Asterisk; break;
                case '{': tok = tokens::LSquirly; break;
                case '}': tok = tokens::RSquirly; break;
                case '[': tok = tokens::LBracket; break;
                case ']': tok = tokens::RBracket; break;
                case ';': tok = tokens::Semicolon; break;
                case '"': 
                    tok.type = tokens::String.type;
                    tok.literal = readString({ iter, sourceCode.end() });
                    iter += (tok.literal.size() - 1);
                    break;
                case '=':
                    if (peek(iter, sourceCode) == '=') {
                        ++iter;
                        tok = tokens::Eq;
                    }
                    else {
                        tok = tokens::Assign;
                    }
                    break;
                case '!':
                    if (peek(iter, sourceCode) == '=') {
                        ++iter;
                        tok = tokens::Ne;
                    }
                    else {
                        tok = tokens::Bang;
                    }
                    break;
                default:
                    if (str::isLetter(*iter)) {
                        tok.literal = readIdentifier({ iter, sourceCode.end() });
                        tok.type = lookupIdent(tok.literal);
                        iter += (tok.literal.length() - 1);
                    }
                    else if (str::isDigit(*iter)) {
                        tok = tokens::Int;
                        tok.literal = readNumber({ iter, sourceCode.end() });
                        iter += (tok.literal.length() - 1);
                    }
                    else {
                        tok = tokens::Illegal;
                        tok.literal = std::string_view{ iter, iter + 1 };
                    }
                    break;
            }

            ++iter;
            co_yield tok;
        }

        tok = tokens::EOF;
        co_yield tok;
    }

}    // namespace arti::monkey
