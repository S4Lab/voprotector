#include "rose.h"

#include "dividevoencoder.h"

using namespace std;


DivideVoEncoder::DivideVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 2);
    left = children.front ();
    ROSE_ASSERT (left);
    right = children.back ();
    ROSE_ASSERT (right);
    left->setOffset (1);
    right->setOffset (1 + left->getSize ());
}

int DivideVoEncoder::getSize () const {
    return 1 + left->getSize () + right->getSize ();
}

void DivideVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "DivideVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x14, "0x14")));
    left->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    right->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

