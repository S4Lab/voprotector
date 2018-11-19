#ifndef NOT_VO_ENCODER_H
#define NOT_VO_ENCODER_H

#include "voencoder.h"


class NotVoEncoder : public VoEncoder {
private:
    VoEncoderPtr operand;

public:
    NotVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
