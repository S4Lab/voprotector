#include "rose.h"

#include "addressofvoencoder.h"

using namespace std;


AddressOfVoEncoder::AddressOfVoEncoder (VoEncoderPtr _operand) :
        VoEncoder (0, TypedValue::instantiatePointerType (_operand->getTypedValue ())),
        operand (_operand) {
    operand->setOffset (1);
}

int AddressOfVoEncoder::getSize () const {
    return 1 + operand->getSize ();
}

void AddressOfVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "AddressOfVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x0D, "0x0D")));

    operand->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

