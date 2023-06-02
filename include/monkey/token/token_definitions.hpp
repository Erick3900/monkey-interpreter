#pragma once

#include <unordered_map>

#include "token/token.hpp"

#ifdef EOF
#    undef EOF
#endif

namespace arti::monkey {

    namespace tokens {

        inline const Token EOF{ "EOF", "" };
        inline const Token Illegal{ "Illegal", "illegal" };

        inline const Token Int{ "Int", "int" };
        inline const Token Ident{ "Ident", "ident" };
        inline const Token String{ "String", "string" };

        inline const Token Dot{ "Dot", "." };
        inline const Token Mod{ "Modulo", "%" };
        inline const Token Plus{ "Plus", "+" };
        inline const Token Bang{ "Bang", "!" };
        inline const Token Minus{ "Minus", "-" };
        inline const Token Slash{ "Slash", "/" };
        inline const Token Colon{ "Colon", ":" };
        inline const Token Assign{ "Assign", "=" };
        inline const Token Asterisk{ "Asterisk", "*" };

        inline const Token Lt{ "LessThan", "<" };
        inline const Token Gt{ "GreaterThan", ">" };

        inline const Token Eq{ "Equal", "==" };
        inline const Token Ne{ "Not Equal", "!=" };

        inline const Token Comma{ "Comma", "," };
        inline const Token Semicolon{ "Semicolon", ";" };

        inline const Token LParen{ "Left Paren", "(" };
        inline const Token RParen{ "Right Paren", ")" };
        inline const Token LSquirly{ "Left Squirly", "{" };
        inline const Token RSquirly{ "Right Squirly", "}" };
        inline const Token LBracket{ "Left Bracket", "[" };
        inline const Token RBracket{ "Right Bracket", "]" };

        inline const Token If{ "If", "if" };
        inline const Token Or{ "Or", "or" };
        inline const Token Let{ "Let", "let" };
        inline const Token Not{ "Not", "not" };
        inline const Token And{ "And", "and" };
        inline const Token Else{ "Else", "else" };
        inline const Token True{ "True", "true" };
        inline const Token False{ "False", "false" };
        inline const Token Const{ "Const", "const" };
        inline const Token Return{ "Return", "return" };
        inline const Token Function{ "Function", "fn" };

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
