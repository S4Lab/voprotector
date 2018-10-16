#ifndef PNTR_DEREF_VO_ENCODER_H
#define PNTR_DEREF_VO_ENCODER_H

#include "voencoder.h"


class PntrDerefVoEncoder : public VoEncoder {
private:
    VoEncoderPtr basePtr;
    VoEncoderPtr arrayIndex;

public:
    PntrDerefVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
