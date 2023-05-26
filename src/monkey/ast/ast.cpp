#include "ast/ast.hpp"

#include <sstream>
#include <iostream>

namespace arti::monkey {

    std::string_view Identifier::tokenLiteral() const {
        return token.literal;
    }

    std::string Identifier::toString() const {
        return std::string{ value };
    }


    LetStatement::LetStatement()
        : token{}
        , name(nullptr)
        , value(nullptr) {}

    std::string_view LetStatement::tokenLiteral() const {
        return token.literal;
    }

    std::string LetStatement::toString() const {
        std::stringstream ss;

        ss << tokenLiteral() << " " << name->toString() << " = ";

        if (value) {
            ss << value->toString();
        }

        ss << ";";

        return ss.str();
    }


    ReturnStatement::ReturnStatement()
        : token{}
        , returnValue(nullptr) {}

    std::string_view ReturnStatement::tokenLiteral() const {
        return token.literal;
    }

    std::string ReturnStatement::toString() const {
        std::stringstream ss;

        ss << tokenLiteral() << " ";

        if (returnValue) {
            ss << returnValue->toString();
        }

        ss << ";";

        return ss.str();
    }


    ExpressionStatement::ExpressionStatement()
        : token{}
        , expression(nullptr) {}

    std::string_view ExpressionStatement::tokenLiteral() const {
        return token.literal;
    }

    std::string ExpressionStatement::toString() const {
        if (expression) {
            return expression->toString();
        }

        return "";
    }


    IntegerLiteral::IntegerLiteral()
        : token{}
        , value(0) {}

    std::string_view IntegerLiteral::tokenLiteral() const {
        return token.literal;
    }

    std::string IntegerLiteral::toString() const {
        return fmt::to_string(value);
    }


    PrefixExpression::PrefixExpression()
        : token{}
        , right(nullptr)
        , op{} {}

    std::string_view PrefixExpression::tokenLiteral() const {
        return token.literal;
    }

    std::string PrefixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << op << right->toString() << ")";

        return ss.str();
    }


    InfixExpression::InfixExpression()
        : token{}
        , left(nullptr)
        , right(nullptr)
        , op{} {}

    std::string_view InfixExpression::tokenLiteral() const {
        return token.literal;
    }

    std::string InfixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << left->toString() << " " << op << " " << right->toString() << ")";

        return ss.str();
    }


    BooleanLiteral::BooleanLiteral()
        : token{}
        , value{false} {}

    std::string_view BooleanLiteral::tokenLiteral() const {
        return token.literal;
    }

    std::string BooleanLiteral::toString() const {
        return fmt::to_string(value);
    }


    std::string Program::toString() const {
        std::stringstream ss;

        for (auto node : statements) {
            ss << node->toString();
        }

        return ss.str();
    }

}    // namespace arti::monkey
