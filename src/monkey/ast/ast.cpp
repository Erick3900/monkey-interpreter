#include "ast/ast.hpp"

#include <sstream>
#include <algorithm>

namespace arti::monkey {

    std::string_view ASTNode::tokenLiteral() const {
        return token.literal;
    }


    std::string Identifier::toString() const {
        return std::string{ value };
    }


    LetStatement::LetStatement()
        : name(nullptr)
        , value(nullptr) {}

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
        : returnValue(nullptr) {}

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
        : expression(nullptr) {}

    std::string ExpressionStatement::toString() const {
        if (expression) {
            return expression->toString();
        }

        return "";
    }


    IntegerLiteral::IntegerLiteral()
        : value(0) {}

    std::string IntegerLiteral::toString() const {
        return fmt::to_string(value);
    }


    PrefixExpression::PrefixExpression()
        : right(nullptr)
        , op{} {}

    std::string PrefixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << op << right->toString() << ")";

        return ss.str();
    }


    BlockStatement::BlockStatement()
        : statements{} {}

    std::string BlockStatement::toString() const {
        std::stringstream ss;

        for (auto statement : statements) {
            ss << statement->toString();
        }

        return ss.str();
    }

    IfExpression::IfExpression()
        : condition(nullptr)
        , consequence(nullptr)
        , alternative(nullptr) {}

    std::string IfExpression::toString() const {
        std::stringstream ss;

        ss << "if " << condition->toString() << " " << consequence->toString();

        if (alternative != nullptr) {
            ss << "else " << alternative->toString();
        }

        return ss.str();
    }


    InfixExpression::InfixExpression()
        : left(nullptr)
        , right(nullptr)
        , op{} {}

    std::string InfixExpression::toString() const {
        std::stringstream ss;

        ss << "(" << left->toString() << " " << op << " " << right->toString() << ")";

        return ss.str();
    }


    BooleanLiteral::BooleanLiteral()
        : value{false} {}

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


    FunctionLiteral::FunctionLiteral()
        : parameters{}
        , statement(nullptr) {}

    std::string FunctionLiteral::toString() const {
        std::stringstream ss;

        std::list<std::string> parametersStrs;

        std::ranges::for_each(parameters, [&](Identifier *p) {
            parametersStrs.emplace_back(p->toString());
        });

        ss << tokenLiteral();
        ss << fmt::format("({})", fmt::join(parametersStrs, ", "));
        ss << statement->toString();

        return ss.str();
    }

    CallExpression::CallExpression()
        : function(nullptr) 
        , arguments{} {}

    std::string CallExpression::toString() const {
        std::stringstream ss;

        std::list<std::string> argsStrs;

        std::ranges::for_each(arguments, [&](ASTNode *a) {
            argsStrs.emplace_back(a->toString());
        });

        ss << function->toString();
        ss << fmt::format("({})", fmt::join(argsStrs, ", "));

        return ss.str();
    }

}    // namespace arti::monkey
