#include "InstructionHandlerState.h"
#include "iostream"
#include "../ObjectCodeGenerator/Constants.h"
#include "../tables/InstructionTypeTable.h"
#include "../LocationCounter.h"
#include "Logger.h"
#include "LoggerConstants.h"

using namespace std;

const string FIXED_INCREMENT = "3";

InstructionHandlerState::InstructionHandlerState(HandlerContext *context)
{
    this->context = context;
}

bool isDirective(string statement) {
    return (statement == Constants::WORD || statement == Constants::BYTE
             || statement == Constants::RESW || statement == Constants::RESB
             || statement == Constants::START);
}

void InstructionHandlerState::handle(string statement)
{
    ///check valid instruction (opCode Table);
    if (!InstructionTypeTable::searchOperation(statement)) {
        throwError();
    }
    ///check for label state
    if(!InstructionTypeTable::getLabelState(statement) && labelAvailable) {
        throwError();
    }
    ///location counter increment
   if (!isDirective(statement)) {
        Logger::log("Using Normal Increment", LoggerConstants::DEBUG);
        LocationCounter::increment(FIXED_INCREMENT);
    }
    /// this part for testing the operand..
    StateHandler::instruction = statement;

    /// If there are no errors .. upgrade the state.
    this->context->setState(context->getOperandHandler());
    //cout << "Currently: operand-handler-state" << endl;
}

void InstructionHandlerState::throwError()
{
    cout << endl << "Invlaid Instruction Syntax" << endl;
}
