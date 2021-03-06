#ifndef ADD_VO_ENCODER_H
#define ADD_VO_ENCODER_H

#include "voencoder.h"


class AddVoEncoder : public VoEncoder {
private:
    VoEncoderPtr left;
    VoEncoderPtr right;

public:
    AddVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
