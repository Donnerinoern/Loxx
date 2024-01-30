#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <list>
#include <map>
#include <string>
#include <string_view>

class Scanner {
    public:
        Scanner(std::string_view source);
        std::list<Token> scan_tokens();
    private:
        void scan_token();
        bool is_at_end();
        char advance();
        void add_token(Token::Type);
        void add_token(Token::Type, std::string_view literal);
        void add_token(Token::Type, double literal);
        void identifier();
        void string();
        bool match(char expected);
        char peek();
        char peek_next();
        void number();

        std::string_view m_source;
        std::list<Token> m_tokens;
        size_t m_start {0};
        size_t m_current {0};
        size_t m_line {1};

        const std::map<std::string, Token::Type> m_keywords {
            {"and", Token::AND},
            {"class", Token::CLASS},
            {"else", Token::ELSE},
            {"false", Token::FALSE},
            {"for", Token::FOR},
            {"fun", Token::FUN},
            {"if", Token::IF},
            {"nil", Token::NIL},
            {"or", Token::OR},
            {"print", Token::PRINT},
            {"return", Token::RETURN},
            {"super", Token::SUPER},
            {"this", Token::THIS},
            {"true", Token::TRUE},
            {"var", Token::VAR},
            {"while", Token::WHILE}
        };
};

#endif
