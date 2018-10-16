#ifndef JUMP_VO_ENCODER_H
#define JUMP_VO_ENCODER_H

#include "voencoder.h"


class JumpVoEncoder : public VoEncoder {
private:
    VoEncoderPtr jumpAmount;

public:
    JumpVoEncoder (int32_t _jumpAmount);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
