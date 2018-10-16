#ifndef PRINTF_VO_ENCODER_H
#define PRINTF_VO_ENCODER_H

#include "voencoder.h"


class PrintfVoEncoder : public VoEncoder {
private:
    VoEncoderPtr format;

public:
    PrintfVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
