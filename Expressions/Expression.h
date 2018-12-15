//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_EXPRESSION_H
#define FIRSTPROJECT_EXPRESSION_H
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
};
#endif //FIRSTPROJECT_EXPRESSION_H
