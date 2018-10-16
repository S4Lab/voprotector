#include "rose.h"

#include "strcmpvoencoder.h"
#include "sequencevoencoder.h"

using namespace std;


StrcmpVoEncoder::StrcmpVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 2); // encoders for {front==SgFunctionRefExp, back==SgExprListExp}
    args = children.back (); // sequence of encoders for s1 and s2 string arguments
    ROSE_ASSERT (args);
    ROSE_ASSERT (dynamic_cast<SequenceVoEncoder *> (args.get ())->getNumberOfChildren () == 2);
    args->setOffset (1);
    cerr << "StrcmpVoEncoder()\n";
}

int StrcmpVoEncoder::getSize () const {
    return 1 + args->getSize ();
}

void StrcmpVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "StrcmpVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x10, "0x10")));
    args->encode (absoluteOffset, globalVariables, program_text, init_func_body);
}

