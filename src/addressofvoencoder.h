#ifndef ADDRESS_OF_VO_ENCODER_H
#define ADDRESS_OF_VO_ENCODER_H

#include "voencoder.h"


class AddressOfVoEncoder : public VoEncoder {
private:
    VoEncoderPtr operand;

public:
    AddressOfVoEncoder (VoEncoderPtr _operand);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
