#include "rose.h"

#include "jumpvoencoder.h"
#include "intvoencoder.h"

using namespace std;


JumpVoEncoder::JumpVoEncoder (int32_t _jumpAmount) : VoEncoder (0) {
    jumpAmount = VoEncoderPtr (new IntVoEncoder (_jumpAmount));
    jumpAmount->setOffset (1);
}

int JumpVoEncoder::getSize () const {
    return 1 + jumpAmount->getSize ();
}

void JumpVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "JumpVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x03, "0x03")));
    jumpAmount->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

