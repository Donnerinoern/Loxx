#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <string_view>

class Token {
    public:
        enum Type { 

            LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

            BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

            IDENTIFIER, STRING, NUMBER,

            AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

            END_OF_FILE

        };

        Token(Type type, std::string_view lexeme, std::string_view literal, int line);

        Type get_type() const { return m_type; }
        std::string_view get_lexeme() const { return m_lexeme; }
        std::string_view get_literal() const { return m_literal; }
        int get_line() const { return m_line; }
        std::string str();

    private:
        Type m_type{};
        std::string_view m_lexeme{};
        std::string_view m_literal{};
        int m_line{};
};

#endif
