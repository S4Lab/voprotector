#ifndef MULTIPLY_VO_ENCODER_H
#define MULTIPLY_VO_ENCODER_H

#include "voencoder.h"


class MultiplyVoEncoder : public VoEncoder {
private:
    VoEncoderPtr left;
    VoEncoderPtr right;

public:
    MultiplyVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
