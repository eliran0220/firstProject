cmake_minimum_required(VERSION 3.12)
project(firstProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(firstProject main.cpp Expressions/Expression.h Expressions/BinaryExpression.h Expressions/Number.h Expressions/Plus.h Expressions/Mult.h Expressions/Minus.h Expressions/Div.h ControlSimulator/RunTheSimulator.cpp ControlSimulator/RunTheSimulator.h Commands/Command.h Commands/SleepCommand.cpp Commands/SleepCommand.h Commands/PrintCommand.cpp Commands/PrintCommand.h Useful/CastStringToExpression.cpp Useful/CastStringToExpression.h ServerAndClient/DataReaderServer.cpp ServerAndClient/DataReaderServer.h Expressions/CommandExpression.h Useful/SymbolTable.cpp Useful/SymbolTable.h)