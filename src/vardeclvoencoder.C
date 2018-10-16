#include "rose.h"

#include "vardeclvoencoder.h"
#include "jumpvoencoder.h"
#include "assignvoencoder.h"
#include "addressofvoencoder.h"
#include "varrefvoencoder.h"


using namespace std;


map<string, int> VarDeclVoEncoder::variableNameToAbsoluteOffset;

VarDeclVoEncoder::VarDeclVoEncoder (SgVariableDeclaration *varDecl, VoEncoderPtrsList children) : VoEncoder (0) {
    const SgInitializedNamePtrList &vars = varDecl->get_variables ();
    ROSE_ASSERT (vars.size () == 1);
    SgInitializedName *in = vars.front ();
    name = in->get_name ();
    setType (TypedValue::instantiateTypeFromSageType (in->get_type ()));
    skipVarDeclJump = VoEncoderPtr (new JumpVoEncoder (typedValue->getSize ()));
    cerr << "VarDeclVoEncoder(name=" << name << ", type=" << typedValue->toString () << ")\n";
    SgInitializer *init = in->get_initptr ();
    if (init) {
        VoEncoderPtr content;
        for (VoEncoderPtrsList::iterator it = children.begin (); it != children.end (); ++it) {
            VoEncoderPtr ptr = *it;
            if (ptr) {
                ROSE_ASSERT (content == NULL);
                content = ptr;
            }
        }
        ROSE_ASSERT (content);
        VoEncoderPtr varRef = VoEncoderPtr (new VarRefVoEncoder (name, typedValue));
        VoEncoderPtr dest = VoEncoderPtr (new AddressOfVoEncoder (varRef));
        assignEncoder = VoEncoderPtr (new AssignVoEncoder (dest, content));
        assignEncoder->setOffset (skipVarDeclJump->getSize () + typedValue->getSize ());
    }
}

int VarDeclVoEncoder::getSize () const {
    return skipVarDeclJump->getSize ()
        + typedValue->getSize ()
        + (assignEncoder ? assignEncoder->getSize () : 0);
}

void VarDeclVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "VarDeclVoEncoder::encode; name=" << name << ", type=" << typedValue->toString () << endl;
    const int absoluteOffset = parentAbsoluteOffset + offset;
    skipVarDeclJump->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    const int variableSize = typedValue->getSize ();
    for (int i = 0; i < variableSize; ++i) {
        program_text->append_expression (SageBuilder::buildAssignInitializer
                (SageBuilder::buildCharVal_nfi (0xAB, "'\\xAB'")));
    }
    const int variableAbsoluteOffset = absoluteOffset + skipVarDeclJump->getSize ();
    VarDeclVoEncoder::variableNameToAbsoluteOffset.insert (make_pair (name, variableAbsoluteOffset));

    if (assignEncoder) {
        assignEncoder->encode (absoluteOffset, globalVariables, program_text, init_func_body);
    }
}

