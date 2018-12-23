cmake_minimum_required(VERSION 3.12)
project(firstProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(firstProject main.cpp Expressions/Expression.h Expressions/BinaryExpression.h Expressions/Number.h Expressions/Plus.h Expressions/Mult.h Expressions/Minus.h Expressions/Div.h ControlSimulator/RunTheSimulator.cpp ControlSimulator/RunTheSimulator.h Commands/Command.h Commands/SleepCommand.cpp Commands/SleepCommand.h Commands/PrintCommand.cpp Commands/PrintCommand.h Useful/FactoryExpression.cpp Useful/FactoryExpression.h ServerAndClient/DataReaderServer.cpp ServerAndClient/DataReaderServer.h Expressions/CommandExpression.h Useful/SymbolTable.cpp Useful/SymbolTable.h Commands/FactoryCommands.cpp Commands/FactoryCommands.h Useful/CollectionCommands.cpp Useful/CollectionCommands.h Commands/DefineVarCommand.cpp Commands/DefineVarCommand.h Useful/Factory.h Commands/InitializeCommand.cpp Commands/InitializeCommand.h Commands/IncreaseCounterCommand.h Commands/ConditionParser.cpp Commands/ConditionParser.h Commands/IfCommand.cpp Commands/IfCommand.h Commands/WhileCommmand.cpp Commands/WhileCommmand.h Commands/OpenServerCommand.cpp Commands/OpenServerCommand.h ServerAndClient/DataReaderClient.cpp ServerAndClient/DataReaderClient.h Commands/ClientCommand.cpp Commands/ClientCommand.h Commands/EntercCommand.cpp Commands/EntercCommand.h)

SET(CMAKE_CXX_FLAGS -pthread)