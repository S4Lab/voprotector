#include "rose.h"

#include "conditionvoencoder.h"


using namespace std;


ConditionVoEncoder::ConditionVoEncoder (ConditionType _type, VoEncoderPtrsList children) :
        VoEncoder (0),
        leftOperand (children.front ()),
        rightOperand (children.back ()),
        type (_type) {
    ROSE_ASSERT (children.size () == 2);
    leftOperand->setOffset (1);
    rightOperand->setOffset (1 + leftOperand->getSize ());
}

int ConditionVoEncoder::getSize () const {
    return 1 + leftOperand->getSize () + rightOperand->getSize () + 1;
}

void ConditionVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "ConditionVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x06, "0x06")));
    leftOperand->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    rightOperand->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    stringstream ss;
    ss << "0x" << hex << uppercase << setw (2) << setfill ('0') << int32_t(type & 0xFF);
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (type, ss.str ())));
}

