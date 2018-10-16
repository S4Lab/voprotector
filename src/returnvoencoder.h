#ifndef RETURN_VO_ENCODER_H
#define RETURN_VO_ENCODER_H

#include "voencoder.h"


class ReturnVoEncoder : public VoEncoder {
private:
    VoEncoderPtr retVal;

public:
    ReturnVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
