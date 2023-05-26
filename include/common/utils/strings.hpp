#pragma once

namespace arti::str {

    static constexpr bool isLetter(char c) {
        return (
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_'
        );
    }

    static constexpr bool isWhitespace(char c) {
        return (
            (c == ' ') ||
            (c == '\t') ||
            (c == '\n') ||
            (c == '\r')
        );
    }

    static constexpr bool isDigit(char c) {
        return (
            c >= '0' && c <= '9'
        );
    }

}
