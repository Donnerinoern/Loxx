#include "scanner.h"
#include "main.h"
#include "token.h"
#include <cctype>
#include <iostream>
#include <list>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>

Scanner::Scanner(std::string_view source)
    : m_source {source}
{}

std::list<Token> Scanner::scan_tokens() {
    while (!is_at_end()) {
        m_start = m_current;
        scan_token();
    }
    m_tokens.push_back(Token(Token::Type::END_OF_FILE, "", "", m_line));
    return m_tokens;
}

bool Scanner::is_at_end() {
    return m_current >= m_source.length();
}

char Scanner::advance() {
    return m_source.at(m_current++);
}

void Scanner::add_token(Token::Type type) {
    add_token(type, "");
}

void Scanner::add_token(Token::Type type, std::string_view literal) {
    std::string_view text = m_source.substr(m_start, m_current-m_start);
    m_tokens.push_back(Token(type, text, literal, m_line));
}

// void Scanner::add_token(Token::Type type, double literal) {
//     // std::string text = std::string {m_source.substr(m_start, m_current)};
//     std::string_view text = m_source.substr(m_start, m_current);
//     m_tokens.push_back(Token(type, text, literal, m_line));
// }

void Scanner::scan_token() {
    char c = advance();
    switch (c) {
        case '(': add_token(Token::LEFT_PAREN); break;
        case ')': add_token(Token::RIGHT_PAREN); break;
        case '{': add_token(Token::LEFT_BRACE); break;
        case '}': add_token(Token::RIGHT_BRACE); break;
        case ',': add_token(Token::COMMA); break;
        case '.': add_token(Token::DOT); break;
        case '-': add_token(Token::MINUS); break;
        case '+': add_token(Token::PLUS); break;
        case ';': add_token(Token::SEMICOLON); break;
        case '*': add_token(Token::STAR); break;
        case '!': add_token(match('=') ? Token::BANG_EQUAL : Token::BANG);
                  break;
        case '=': add_token(match('=') ? Token::EQUAL_EQUAL : Token::EQUAL);
                  break;
        case '<': add_token(match('=') ? Token::LESS_EQUAL : Token::LESS);
                  break;
        case '>': add_token(match('=') ? Token::GREATER_EQUAL : Token::GREATER);
                  break;
        case '/':
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) advance();
            } else {
                add_token(Token::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            m_line++;
            break;
        case '"': string(); break;
        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c)) {
                identifier();
            } else {
                Lox::error(m_line, "Unexpected character.");
                break;
            }
    }
}

void Scanner::identifier() {
    while (std::isalnum(peek())) advance();

    std::string text { m_source.substr(m_start, m_current-m_start) };

    Token::Type type;
    if (m_keywords.contains(text)) {
        type = m_keywords.at(text);
    } else {
        type = Token::IDENTIFIER;
    }

    add_token(type);
}

void Scanner::string() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') m_line++;
        advance();
    }

    if (is_at_end()) {
        Lox::error(m_line, "Unterminated string.");
        return;
    }

    advance();

    add_token(Token::STRING, m_source.substr(m_start + 1, m_current-(m_start+2)));
}

bool Scanner::match(char expected) {
    if (is_at_end()) return false;
    if (m_source.at(m_current) != expected) return false;

    m_current++;
    return true;
}

char Scanner::peek() {
    if (is_at_end()) return '\0';
    return m_source.at(m_current);
}

char Scanner::peek_next() {
    if (m_current + 1 >= m_source.length()) return '\0';
    return m_source.at(m_current + 1);
}

void Scanner::number() {
    while (std::isdigit(peek())) advance();

    if (peek() == '.' && std::isdigit(peek_next())) {
        advance();

        while (std::isdigit(peek())) advance();
    }

    add_token(Token::NUMBER, m_source.substr(m_start, m_current-m_start));
}
