#include "rose.h"

#include "minusvoencoder.h"

using namespace std;


MinusVoEncoder::MinusVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 1);
    operand = children.front ();
    ROSE_ASSERT (operand);
    operand->setOffset (1);
}

int MinusVoEncoder::getSize () const {
    return 1 + operand->getSize ();
}

void MinusVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "MinusVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x05, "0x05")));
    operand->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

