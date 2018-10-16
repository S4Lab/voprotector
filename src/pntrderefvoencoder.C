#include "rose.h"

#include "pntrderefvoencoder.h"

using namespace std;


PntrDerefVoEncoder::PntrDerefVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 2);

    basePtr = children.front ();
    basePtr->setOffset (1);
    ROSE_ASSERT (basePtr->getTypedValue ()->isPointer ());
    setType (basePtr->getTypedValue ()->getDereferencedType ());

    arrayIndex = children.back ();
    arrayIndex->setOffset (1 + basePtr->getSize ());
    cerr << "PntrDerefVoEncoder(dereferenced/final type=" << typedValue->toString () << ")\n";
}

int PntrDerefVoEncoder::getSize () const {
    return 1 + basePtr->getSize () + arrayIndex->getSize ();
}

void PntrDerefVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "PntrDerefVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    const int encodedType = 0x09 + typedValue->getType ();
    stringstream ss;
    ss << "0x" << hex << uppercase << setw (2) << setfill ('0') << int32_t(encodedType & 0xFF);
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (encodedType, ss.str ())));

    basePtr->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    arrayIndex->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

