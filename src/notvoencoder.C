#include "rose.h"

#include "notvoencoder.h"

using namespace std;


NotVoEncoder::NotVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 1);
    operand = children.front ();
    ROSE_ASSERT (operand);
    operand->setOffset (1);
}

int NotVoEncoder::getSize () const {
    return 1 + operand->getSize ();
}

void NotVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "NotVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x15, "0x15")));
    operand->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

