#ifndef REMAINDER_VO_ENCODER_H
#define REMAINDER_VO_ENCODER_H

#include "voencoder.h"


class RemainderVoEncoder : public VoEncoder {
private:
    VoEncoderPtr left;
    VoEncoderPtr right;

public:
    RemainderVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
