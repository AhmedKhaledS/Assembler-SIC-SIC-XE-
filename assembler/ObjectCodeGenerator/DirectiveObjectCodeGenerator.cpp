#include "DirectiveObjectCodeGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include "../NumberConverters/HexadecimalConverter.h"
#include "Constants.h"

using namespace std;

DirectiveObjectCodeGenerator::DirectiveObjectCodeGenerator(string oper, string inst) {
    operand = oper;
    instruction = inst;
}

string fillZeros(string code) {
    int requiredZeros = Constants::OBJECT_CODE_SIZE - code.length();
    string zeros = "";
    for (int i = 0; i < requiredZeros; i++) {
        zeros += "0";
    }
    zeros.append(code);
    return zeros;
}

string DirectiveObjectCodeGenerator::handleWord() {
    string objectCode;
    if (operand[0] == Constants::HEX_PREFIX) {
        return operand.substr(2, operand.length() - 3);
    } else {
        return HexadecimalConverter::convertDecToHex(operand);
    }
    if (objectCode.length() < Constants::OBJECT_CODE_SIZE) {
        return fillZeros(objectCode);
    }
    return objectCode;
}

string DirectiveObjectCodeGenerator::handleByte() {
     string objectCode;
     if (operand[0] == Constants::HEX_PREFIX) {
        return objectCode = operand.substr(2, operand.length() - 3);
     } else if (operand[0] == Constants::CHAR_PREFIX) {
        for (int i = 2; i < operand.length() - 1; i++) {
            objectCode += HexadecimalConverter::convertDecToHex(operand[i]);
        }
     }
     if (objectCode.length() < Constants::OBJECT_CODE_SIZE) {
        return fillZeros(objectCode);
    }
     return objectCode;
}

string DirectiveObjectCodeGenerator::parse() {
    if (instruction == Constants::WORD) {
        return handleWord();
    } else if (instruction == Constants::BYTE) {
        return handleByte();
    }
    return "";
}
