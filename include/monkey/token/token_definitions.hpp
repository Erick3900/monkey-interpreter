#pragma once

#include <unordered_map>

#include "token/token.hpp"

#ifdef EOF
#    undef EOF
#endif

namespace arti::monkey {

    namespace tokens {

        inline constexpr Token EOF{ "EOF", "" };
        inline constexpr Token Illegal{ "Illegal", "illegal" };

        inline constexpr Token Int{ "Int", "int" };
        inline constexpr Token Ident{ "Ident", "ident" };
        inline constexpr Token String{ "String", "string" };

        inline constexpr Token Dot{ "Dot", "." };
        inline constexpr Token Mod{ "Modulo", "%" };
        inline constexpr Token Plus{ "Plus", "+" };
        inline constexpr Token Bang{ "Bang", "!" };
        inline constexpr Token Minus{ "Minus", "-" };
        inline constexpr Token Slash{ "Slash", "/" };
        inline constexpr Token Colon{ "Colon", ":" };
        inline constexpr Token Assign{ "Assign", "=" };
        inline constexpr Token Asterisk{ "Asterisk", "*" };

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
        inline constexpr Token LBracket{ "Left Bracket", "[" };
        inline constexpr Token RBracket{ "Right Bracket", "]" };

        inline constexpr Token If{ "If", "if" };
        inline constexpr Token Or{ "Or", "or" };
        inline constexpr Token Let{ "Let", "let" };
        inline constexpr Token Not{ "Not", "not" };
        inline constexpr Token And{ "And", "and" };
        inline constexpr Token Else{ "Else", "else" };
        inline constexpr Token True{ "True", "true" };
        inline constexpr Token False{ "False", "false" };
        inline constexpr Token Const{ "Const", "const" };
        inline constexpr Token Return{ "Return", "return" };
        inline constexpr Token Function{ "Function", "fn" };

    }    // namespace tokens

    inline std::unordered_map<Literal_t, Token_t> keywords{
        {    "fn", tokens::Function.type},
        {    "if",       tokens::If.type},
        {    "or",       tokens::Or.type},
        {   "let",      tokens::Let.type},
        {   "not",      tokens::Not.type},
        {   "and",      tokens::And.type},
        {  "else",     tokens::Else.type},
        { "const",    tokens::Const.type},
        {  "true",     tokens::True.type},
        { "false",    tokens::False.type},
        {"return",   tokens::Return.type},
    };

}    // namespace arti::monkey
