//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_EXPRESSION_H
#define FIRSTPROJECT_EXPRESSION_H

#include <string>
#include <vector>

using namespace std;


class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression(){}

    bool operator<(Expression *expression){
        return this->calculate() < expression->calculate();
    }
    bool operator<=(Expression *expression){
        return this->calculate() <= expression->calculate();
    }
    bool operator>(Expression *expression){
        return this->calculate() > expression->calculate();
    }

    bool operator>=(Expression *expression){
        return this->calculate() >= expression->calculate();
    }

    virtual void setLexerStringAndPosition(vector<string>* parameters, int position){}
};
#endif //FIRSTPROJECT_EXPRESSION_H
