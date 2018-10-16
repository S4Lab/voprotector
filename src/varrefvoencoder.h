#ifndef VAR_REF_VO_ENCODER_H
#define VAR_REF_VO_ENCODER_H

#include "voencoder.h"


class VarRefVoEncoder : public VoEncoder {
private:
    std::string name;
    bool isArgc;

public:
    VarRefVoEncoder (SgVarRefExp *varRef);
    VarRefVoEncoder (std::string _name, TypedValuePtr _type);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;

    std::string getName () const;

private:
    virtual void encodeVarByOffset (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
    virtual void encodeArgc (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
