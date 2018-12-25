#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <vector>

using namespace std;

/**
 * Expression class: The Expression class is supposed to create a basic
 * expression
 */
class Expression {

public:
    virtual double calculate() = 0;

    virtual ~Expression() {}

    /**
     * Function name: operator<
     * The function operation: The function returns true if left expression is less than right expression,
     * else return false
     * @param expression
     * @return bool
     */
    bool operator<(Expression *expression) {
        return this->calculate() < expression->calculate();
    }

    /**
     * Function name: operator<=
     * The function operation: The function returns true if left expression is less equal than right expression,
     * else return false
     * @param expression
     * @return bool
     */
    bool operator<=(Expression *expression) {
        return this->calculate() <= expression->calculate();
    }

    /**
     * Function name: operator>
     * The function operation: The function returns true if left expression is bigger than right expression,
     * else return false
     * @param expression
     * @return bool
     */
    bool operator>(Expression *expression) {
        return this->calculate() > expression->calculate();
    }

    /**
     * Function name: operator>=
     * The function operation: The function returns true if left expression is bigger equal than right expression,
     * else return false
     * @param expression
     * @return bool
     */
    bool operator>=(Expression *expression) {
        return this->calculate() >= expression->calculate();
    }

    /**
     * Function name: operator==
     * The function operation: The function returns true if left expression is equal to right expression,
     * else return false
     * @param expression
     * @return bool
     */
    bool operator==(Expression *expression) {
        return this->calculate() == expression->calculate();
    }

    /**
     * Function name: operator!=
     * The function operation: The function returns true if left expression is not equal to right expression,
     * else return false
     * @param expression
     * @return bool
     */
    bool operator!=(Expression *expression) {
        return this->calculate() != expression->calculate();
    }

    /**
     * Function name: setLexerStringAndPosition
     * The function operation: The function sets the lexer to the position of the vector.
     * Each time the position changes, and so the lexer reads the next line
     * @param vector<string>, int
     * @return void
     */
    virtual void
    setLexerStringAndPosition(vector<string> *parameters, int position) {}
};

#endif
