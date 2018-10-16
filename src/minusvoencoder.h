#ifndef MINUS_VO_ENCODER_H
#define MINUS_VO_ENCODER_H

#include "voencoder.h"


class MinusVoEncoder : public VoEncoder {
private:
    VoEncoderPtr operand;

public:
    MinusVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
