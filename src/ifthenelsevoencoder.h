#ifndef IF_THEN_ELSE_VO_ENCODER_H
#define IF_THEN_ELSE_VO_ENCODER_H

#include "voencoder.h"


class IfThenElseVoEncoder : public VoEncoder {
private:
    VoEncoderPtr condition;
    bool hasElsePart;
    VoEncoderPtr thenOffset;
    VoEncoderPtr elseOffset;
    VoEncoderPtr thenPart;
    VoEncoderPtr skipElsePartJump;
    VoEncoderPtr elsePart;

public:
    IfThenElseVoEncoder (VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
