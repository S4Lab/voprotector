#include "rose.h"

#include "returnvoencoder.h"

using namespace std;


ReturnVoEncoder::ReturnVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 1);
    //IntVoEncoder *ivoe = dynamic_cast<IntVoEncoder *> (children.front ().get ());
    //ROSE_ASSERT (ivoe != NULL);
    retVal = children.front ();
    ROSE_ASSERT (retVal);
    retVal->setOffset (1);
}

int ReturnVoEncoder::getSize () const {
    return 1 + retVal->getSize ();
}

void ReturnVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "ReturnVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x00, "0x00")));
    retVal->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

