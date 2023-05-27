#pragma once

#include <unordered_map>

#include "token/token.hpp"

#ifdef EOF
#    undef EOF
#endif

namespace arti::monkey {

    namespace tokens {

        inline constexpr Token Illegal{ "Illegal", "illegal" };
        inline constexpr Token EOF{ "EOF", "" };

        inline constexpr Token Ident{ "Ident", "ident" };
        inline constexpr Token Int{ "Int", "int" };

        inline constexpr Token Assign{ "Assign", "=" };
        inline constexpr Token Plus{ "Plus", "+" };
        inline constexpr Token Minus{ "Minus", "-" };
        inline constexpr Token Bang{ "Bang", "!" };
        inline constexpr Token Asterisk{ "Asterisk", "*" };
        inline constexpr Token Slash{ "Slash", "/" };

        inline constexpr Token Lt{ "LessThan", "<" };
        inline constexpr Token Gt{ "GreaterThan", ">" };

        inline constexpr Token Eq{ "Equal", "==" };
        inline constexpr Token Ne{ "Not Equal", "!=" };

        inline constexpr Token Comma{ "Comma", "," };
        inline constexpr Token Semicolon{ "Semicolon", ";" };

        inline constexpr Token LParen{ "Left Paren", "(" };
        inline constexpr Token RParen{ "Right Paren", ")" };
        inline constexpr Token LSquirly{ "Left Squirly", "{" };
        inline constexpr Token RSquirly{ "Right Squirly", "}" };

        inline constexpr Token Function{ "Function", "fn" };
        inline constexpr Token Let{ "Let", "let" };
        inline constexpr Token True{ "True", "true" };
        inline constexpr Token False{ "False", "false" };
        inline constexpr Token If{ "If", "if" };
        inline constexpr Token Else{ "Else", "else" };
        inline constexpr Token Return{ "Return", "return" };

    }    // namespace tokens

    inline std::unordered_map<Literal_t, Token_t> keywords{
        {    "fn", tokens::Function.type},
        {   "let",      tokens::Let.type},
        {  "true",     tokens::True.type},
        { "false",    tokens::False.type},
        {    "if",       tokens::If.type},
        {  "else",     tokens::Else.type},
        {"return",   tokens::Return.type}
    };

}    // namespace arti::monkey
