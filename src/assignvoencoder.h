#ifndef ASSIGN_VO_ENCODER_H
#define ASSIGN_VO_ENCODER_H

#include "voencoder.h"


class AssignVoEncoder : public VoEncoder {
private:
    VoEncoderPtr dest;
    VoEncoderPtr content;

public:
    AssignVoEncoder (VoEncoderPtrsList children);
    AssignVoEncoder (VoEncoderPtr _dest, VoEncoderPtr _content);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
