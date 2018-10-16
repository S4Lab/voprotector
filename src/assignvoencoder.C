#include "rose.h"

#include "assignvoencoder.h"
#include "addressofvoencoder.h"

using namespace std;


AssignVoEncoder::AssignVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 2);
    VoEncoderPtr lhs = children.front ();
    ROSE_ASSERT (lhs);
    dest = VoEncoderPtr (new AddressOfVoEncoder (lhs));
    dest->setOffset (1);
    setType (lhs->getTypedValue ());
    content = children.back ();
    ROSE_ASSERT (content);
    content->setOffset (1 + dest->getSize ());
}

AssignVoEncoder::AssignVoEncoder (VoEncoderPtr _dest, VoEncoderPtr _content) :
        VoEncoder (0),
        dest (_dest),
        content (_content) {
    dest->setOffset (1);
    setType (_dest->getTypedValue ());
    content->setOffset (1 + dest->getSize ());
}

int AssignVoEncoder::getSize () const {
    return 1 + dest->getSize () + content->getSize () + 1;
}

void AssignVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "AssignVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x05, "0x05")));

    dest->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    content->encode (absoluteOffset, globalVariables, program_text, init_func_body);

    const int encodedType = typedValue->getType ();
    stringstream ss;
    ss << "0x" << hex << uppercase << setw (2) << setfill ('0') << int32_t(encodedType & 0xFF);
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (encodedType, ss.str ())));
}

