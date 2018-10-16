#ifndef INT_VO_ENCODER_H
#define INT_VO_ENCODER_H

#include "voencoder.h"


class IntVoEncoder : public VoEncoder {
private:
    int32_t value;

public:
    IntVoEncoder (int32_t _value);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
