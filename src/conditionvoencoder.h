#ifndef CONDITION_VO_ENCODER_H
#define CONDITION_VO_ENCODER_H

#include "voencoder.h"


class ConditionVoEncoder : public VoEncoder {
public:
    enum ConditionType {
        LessThan = 0x1,
        LessOrEqual = 0x2,
        GreaterThan = 0x3,
        GreaterOrEqual = 0x4,
        Equal = 0x5,
        NonEqual = 0x6,
        BooleanAnd = 0x7,
        BooleanOr = 0x8,
    };

private:
    VoEncoderPtr leftOperand;
    VoEncoderPtr rightOperand;
    ConditionType type;

public:
    ConditionVoEncoder (ConditionType _type, VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
