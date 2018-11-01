#ifndef ROOT_VO_ENCODER_H
#define ROOT_VO_ENCODER_H

#include "sequencevoencoder.h"


class RootVoEncoder : public SequenceVoEncoder {
private:
    SgGlobal *globalScope;
    SgFunctionDeclaration *mainDec;

public:
    RootVoEncoder (SgGlobal *_globalScope, SgFunctionDeclaration *_mainDec, VoEncoderPtrsList _children);
    
    void encode () const;

private:
    void replaceMain (SgFunctionDeclaration *mainDec,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgFunctionDeclaration *init_program_func) const;

    SgFunctionDeclaration *buildInitProgramFunction () const;
};

#endif
