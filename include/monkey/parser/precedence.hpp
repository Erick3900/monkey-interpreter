#pragma once

namespace arti::monkey {

    namespace expressions {
        enum Precedence {
            _,
            LOWEST,
            ASSIGN,
            EQUALS,
            LESS_GREATER,
            SUM,
            PRODUCT,
            PREFIX,
            CALL,
            INDEX,
        };
    }

}
