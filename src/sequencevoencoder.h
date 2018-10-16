#ifndef SEQUENCE_VO_ENCODER
#define SEQUENCE_VO_ENCODER

#include "voencoder.h"


class SequenceVoEncoder : public VoEncoder {
private:
    VoEncoderPtrsList children;

public:
    SequenceVoEncoder (VoEncoderPtrsList _children);

    int getNumberOfChildren () const;
        
    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
