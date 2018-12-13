cmake_minimum_required(VERSION 3.12)
project(firstProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(firstProject main.cpp Expressions/Expression.h Expressions/BinaryExpression.h Expressions/Number.h Expressions/Plus.h Expressions/Mult.h Expressions/Minus.h Expressions/Div.h)