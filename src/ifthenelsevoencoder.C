#include "rose.h"

#include "ifthenelsevoencoder.h"
#include "intvoencoder.h"
#include "jumpvoencoder.h"

using namespace std;


IfThenElseVoEncoder::IfThenElseVoEncoder (VoEncoderPtrsList children) : VoEncoder (0) {
    ROSE_ASSERT (children.size () == 2 || children.size () == 3);
    int relativeOffset = 1;
    VoEncoderPtrsList::iterator it = children.begin ();
    condition = *it++;
    condition->setOffset (relativeOffset);
    relativeOffset += condition->getSize ();

    thenOffset = VoEncoderPtr (new IntVoEncoder (0));
    thenOffset->setOffset (relativeOffset);
    relativeOffset += thenOffset->getSize ();

    const int elseOffsetRelativeOffset = relativeOffset;
    relativeOffset += thenOffset->getSize (); // == elseOffset->getSize ();

    thenPart = *it++;
    thenPart->setOffset (relativeOffset);
    relativeOffset += thenPart->getSize ();
    hasElsePart = (it != children.end () && *it);
    if (hasElsePart) {
        elsePart = *it;
        skipElsePartJump = VoEncoderPtr (new JumpVoEncoder (elsePart->getSize ()));
        skipElsePartJump->setOffset (relativeOffset);
        relativeOffset += skipElsePartJump->getSize ();
        elsePart->setOffset (relativeOffset);

        elseOffset = VoEncoderPtr (new IntVoEncoder (thenPart->getSize () + skipElsePartJump->getSize ()));
        elseOffset->setOffset (elseOffsetRelativeOffset);
    } else {
        elseOffset = VoEncoderPtr (new IntVoEncoder (thenPart->getSize ()));
        elseOffset->setOffset (elseOffsetRelativeOffset);
    }
}

int IfThenElseVoEncoder::getSize () const {
    return 1
        + condition->getSize ()
        + thenOffset->getSize ()
        + elseOffset->getSize ()
        + thenPart->getSize ()
        + (hasElsePart ? skipElsePartJump->getSize () + elsePart->getSize () : 0);
}

void IfThenElseVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "IfThenElseVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x01, "0x01")));
    condition->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    thenOffset->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    elseOffset->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    thenPart->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    if (hasElsePart) {
        skipElsePartJump->encode (absoluteOffset, globalVariables, program_text, init_func_body);
        elsePart->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    }
}

