#include "rose.h"

#include "sequencevoencoder.h"

using namespace std;


SequenceVoEncoder::SequenceVoEncoder (VoEncoderPtrsList _children) : VoEncoder (0) {
    cerr << "SequenceVoEncoder()\n";
    int childOffset = 0;
    for (VoEncoderPtrsList::iterator it = _children.begin (); it != _children.end (); ++it) {
        VoEncoderPtr voep = *it;
        if (voep) {
            children.push_back (voep);
            voep->setOffset (childOffset);
            childOffset += voep->getSize ();
        }
    }
}

int SequenceVoEncoder::getNumberOfChildren () const {
    return children.size ();
}

int SequenceVoEncoder::getSize () const {
    int size = 0;
    for (VoEncoderPtrsList::const_iterator it = children.begin (); it != children.end (); ++it) {
        const VoEncoderPtr voep = *it;
        size += voep->getSize ();
    }
    return size;
}

void SequenceVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "SequenceVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    for (VoEncoderPtrsList::const_iterator it = children.begin (); it != children.end (); ++it) {
        const VoEncoderPtr voep = *it;
        voep->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    }
}

