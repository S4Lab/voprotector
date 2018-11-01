#ifndef VIRTUALIZATION_OBFUSCATION_PROTECTOR_H
#define VIRTUALIZATION_OBFUSCATION_PROTECTOR_H

#include "voencoder.h"


class VirtualizationObfuscationProtector : public AstBottomUpProcessing<VoEncoderPtr> {
public:
    VirtualizationObfuscationProtector ();

protected:
    VoEncoderPtr evaluateSynthesizedAttribute (SgNode *node, SynthesizedAttributesList synAttributes);

private:
    VoEncoderPtr visitFunctionDeclaration (SgFunctionDeclaration *functionDecl, SynthesizedAttributesList synAttributes) const;
    VoEncoderPtr visitFunction (SgFunctionCallExp *functionCallExp, SynthesizedAttributesList synAttributes) const;
    void print (SgNode *node) const;
};

#endif
