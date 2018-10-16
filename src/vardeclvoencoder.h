#ifndef VAR_DECL_VO_ENCODER_H
#define VAR_DECL_VO_ENCODER_H

#include "voencoder.h"


class VarDeclVoEncoder : public VoEncoder {
public:
    static std::map<std::string, int> variableNameToAbsoluteOffset;

private:
    std::string name;
    VoEncoderPtr skipVarDeclJump;
    VoEncoderPtr assignEncoder;

public:
    VarDeclVoEncoder (SgVariableDeclaration *varDecl, VoEncoderPtrsList children);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
