#include "rose.h"

#include "printfvoencoder.h"
#include "sequencevoencoder.h"

using namespace std;


PrintfVoEncoder::PrintfVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 2); // encoders for {front==SgFunctionRefExp, back==SgExprListExp}
    format = children.back ();
    ROSE_ASSERT (format);
    ROSE_ASSERT (dynamic_cast<SequenceVoEncoder *> (format.get ())->getNumberOfChildren () == 1);
    format->setOffset (1);
    cerr << "PrintfVoEncoder()\n";
}

int PrintfVoEncoder::getSize () const {
    return 1 + format->getSize ();
}

void PrintfVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "PrintfVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x0F, "0x0F")));
    format->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

