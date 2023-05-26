#pragma once

#include <ostream>
#include <string_view>
#include <unordered_map>

#include <fmt/format.h>

#ifdef EOF
static constexpr auto EOF_MACRO = EOF;
#    undef EOF
#endif

namespace arti::monkey {

    using Token_t = std::string_view;
    using Literal_t = std::string_view;

    struct Token {
        Token_t type;
        Literal_t literal;
    };

    static std::ostream &operator<<(std::ostream &os, const Token &token) {
        return os << fmt::format("Token {{\n  type:  '{}',\n  value: '{}'\n}}", token.type, token.literal);
    }

    namespace tokens {

        static constexpr Token Illegal{ "Illegal", "illegal" };
        static constexpr Token EOF{ "EOF", "" };

        static constexpr Token Ident{ "Ident", "ident" };
        static constexpr Token Int{ "Int", "int" };

        static constexpr Token Assign{ "Assign", "=" };
        static constexpr Token Plus{ "Plus", "+" };
        static constexpr Token Minus{ "Minus", "-" };
        static constexpr Token Bang{ "Bang", "!" };
        static constexpr Token Asterisk{ "Asterisk", "*" };
        static constexpr Token Slash{ "Slash", "/" };

        static constexpr Token Lt{ "LessThan", "<" };
        static constexpr Token Gt{ "GreaterThan", ">" };

        static constexpr Token Eq{ "Equal", "==" };
        static constexpr Token Ne{ "Not Equal", "!=" };

        static constexpr Token Comma{ "Comma", "," };
        static constexpr Token Semicolon{ "Semicolon", ";" };

        static constexpr Token LParen{ "Left Paren", "(" };
        static constexpr Token RParen{ "Right Paren", ")" };
        static constexpr Token LSquirly{ "Left Squirly", "{" };
        static constexpr Token RSquirly{ "Right Squirly", "}" };

        static constexpr Token Function{ "Function", "fn" };
        static constexpr Token Let{ "Let", "let" };
        static constexpr Token True{ "True", "true" };
        static constexpr Token False{ "False", "false" };
        static constexpr Token If{ "If", "if" };
        static constexpr Token Else{ "Else", "else" };
        static constexpr Token Return{ "Return", "return" };

    }    // namespace tokens

    static std::unordered_map<Literal_t, Token_t> keywords{
        {    "fn", tokens::Function.type},
        {   "let",      tokens::Let.type},
        {  "true",     tokens::True.type},
        { "false",    tokens::False.type},
        {    "if",       tokens::If.type},
        {  "else",     tokens::Else.type},
        {"return",   tokens::Return.type}
    };

    Token_t lookupIdent(std::string_view ident);

}    // namespace arti::monkey
