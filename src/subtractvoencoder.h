#ifndef SUBTRACT_VO_ENCODER_H
#define SUBTRACT_VO_ENCODER_H

#include "voencoder.h"


class SubtractVoEncoder : public VoEncoder {
private:
    VoEncoderPtr left;
    VoEncoderPtr right;

public:
    SubtractVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
