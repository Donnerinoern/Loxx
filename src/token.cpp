#include "token.h"
#include <string>

Token::Token(Type type, std::string_view lexeme, std::string_view literal, int line)
    : m_type {type}
    , m_lexeme {lexeme}
    , m_literal {literal}
    , m_line {line}
{}

std::string Token::str() {
    std::string string;
    switch (m_type) {
        case AND: string = "AND"; break;
        case CLASS: string = "CLASS"; break;
        case ELSE: string = "ELSE"; break;
        case FALSE: string = "FALSE"; break;
        case FOR: string = "FOR"; break;
        case FUN: string = "FUN"; break;
        case IF: string = "IF"; break;
        case NIL: string = "NIL"; break;
        case OR: string = "OR"; break;
        case PRINT: string = "PRINT"; break;
        case RETURN: string = "RETURN"; break;
        case SUPER: string = "SUPER"; break;
        case THIS: string = "THIS"; break;
        case TRUE: string = "TRUE"; break;
        case VAR: string = "VAR"; break;
        case WHILE: string = "WHILE"; break;
        case NUMBER: string = "NUMBER"; break;
        case STRING: string = "STRING"; break;
        case END_OF_FILE: string = "EOF"; break;
        case LEFT_PAREN: string = "LEFT_PAREN"; break;
        case RIGHT_PAREN: string = "RIGHT_PAREN"; break;
        case SEMICOLON: string = "SEMICOLON"; break;
        case EQUAL: string = "EQUAL"; break;
        case IDENTIFIER: string = "IDENTIFIER"; break;
        default: string = "???";
    }
    string.append(" ");
    string.append(m_lexeme);
    string.append(" ");
    string.append(m_literal);
    string.append("\n");
    return string;
}
