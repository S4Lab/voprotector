#ifndef DIVIDE_VO_ENCODER_H
#define DIVIDE_VO_ENCODER_H

#include "voencoder.h"


class DivideVoEncoder : public VoEncoder {
private:
    VoEncoderPtr left;
    VoEncoderPtr right;

public:
    DivideVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
