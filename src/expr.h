#include "token.h"

class Expr {
};

class Binary: public Expr {
    public:
        Binary(Expr left, Token t_operator, Expr right)
            : m_left {left}
            , m_operator {t_operator}
            , m_right {right}
        {}

        Expr m_left;
        Token m_operator;
        Expr m_right;
};
