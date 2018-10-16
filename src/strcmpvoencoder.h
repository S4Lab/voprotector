#ifndef STRCMP_VO_ENCODER_H
#define STRCMP_VO_ENCODER_H

#include "voencoder.h"


class StrcmpVoEncoder : public VoEncoder {
private:
    VoEncoderPtr args;

public:
    StrcmpVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
