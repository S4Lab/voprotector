#include "rose.h"

#include "virtualizationobfuscationprotector.h"
#include "rootvoencoder.h"
#include "pntrderefvoencoder.h"
#include "vardeclvoencoder.h"
#include "varrefvoencoder.h"
#include "assignvoencoder.h"
#include "notvoencoder.h"
#include "minusvoencoder.h"
#include "subtractvoencoder.h"
#include "addvoencoder.h"
#include "multiplyvoencoder.h"
#include "dividevoencoder.h"
#include "intvoencoder.h"
#include "stringvoencoder.h"
#include "returnvoencoder.h"
#include "conditionvoencoder.h"
#include "ifthenelsevoencoder.h"
#include "printfvoencoder.h"
#include "strcmpvoencoder.h"


using namespace std;


VirtualizationObfuscationProtector::VirtualizationObfuscationProtector () {
}

VoEncoderPtr VirtualizationObfuscationProtector::evaluateSynthesizedAttribute (SgNode *node, SynthesizedAttributesList synAttributes) {
    print (node);
    switch (node->variantT ()) {
        case V_SgFunctionDeclaration:
            return visitFunctionDeclaration (isSgFunctionDeclaration (node), synAttributes);

        case V_SgPntrArrRefExp:
            return VoEncoderPtr (new PntrDerefVoEncoder (synAttributes));

        case V_SgVariableDeclaration:
            return VoEncoderPtr (new VarDeclVoEncoder (isSgVariableDeclaration (node), synAttributes));

        case V_SgVarRefExp:
            return VoEncoderPtr (new VarRefVoEncoder (isSgVarRefExp (node)));

        case V_SgAssignOp:
            return VoEncoderPtr (new AssignVoEncoder (synAttributes));

        case V_SgFunctionCallExp: 
            return visitFunction (isSgFunctionCallExp (node), synAttributes);

        case V_SgNotOp:
            return VoEncoderPtr (new NotVoEncoder (synAttributes));

        case V_SgMinusOp:
            return VoEncoderPtr (new MinusVoEncoder (synAttributes));

        case V_SgSubtractOp:
            return VoEncoderPtr (new SubtractVoEncoder (synAttributes));

        case V_SgAddOp:
            return VoEncoderPtr (new AddVoEncoder (synAttributes));

        case V_SgMultiplyOp:
            return VoEncoderPtr (new MultiplyVoEncoder (synAttributes));

        case V_SgDivideOp:
            return VoEncoderPtr (new DivideVoEncoder (synAttributes));

        case V_SgIntVal:
            return VoEncoderPtr (new IntVoEncoder (isSgIntVal (node)->get_value ()));

        case V_SgStringVal:
            return VoEncoderPtr (new StringVoEncoder (isSgStringVal (node)->get_value ()));

        case V_SgReturnStmt:
            return VoEncoderPtr (new ReturnVoEncoder (synAttributes));

        case V_SgIfStmt:
            return VoEncoderPtr (new IfThenElseVoEncoder (synAttributes));
        case V_SgLessThanOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::LessThan, synAttributes));
        case V_SgLessOrEqualOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::LessOrEqual, synAttributes));
        case V_SgGreaterThanOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::GreaterThan, synAttributes));
        case V_SgGreaterOrEqualOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::GreaterOrEqual, synAttributes));
        case V_SgEqualityOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::Equal, synAttributes));
        case V_SgNotEqualOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::NonEqual, synAttributes));
        case V_SgAndOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::BooleanAnd, synAttributes));
        case V_SgOrOp:
            return VoEncoderPtr (new ConditionVoEncoder (ConditionVoEncoder::BooleanOr, synAttributes));

        default:
            return VoEncoderPtr (new SequenceVoEncoder (synAttributes));
    }
}

VoEncoderPtr VirtualizationObfuscationProtector::visitFunctionDeclaration (
        SgFunctionDeclaration *functionDecl,
        SynthesizedAttributesList synAttributes) const {
    SgGlobal *global = isSgGlobal (isSgStatement (functionDecl)->get_scope ());
    if (global) {
        if (functionDecl->get_name () == "main" && functionDecl->get_definingDeclaration() == functionDecl) {
            throw VoEncoderPtr (new RootVoEncoder (global, functionDecl, synAttributes));
        }
    }
    return VoEncoderPtr (new SequenceVoEncoder (synAttributes));
}

VoEncoderPtr VirtualizationObfuscationProtector::visitFunction (
        SgFunctionCallExp *functionCallExp,
        SynthesizedAttributesList synAttributes) const {
    SgExpression *function = functionCallExp->get_function ();
    ROSE_ASSERT (function);
    ROSE_ASSERT (function->variantT () == V_SgFunctionRefExp);

    SgFunctionRefExp *functionRefExp = isSgFunctionRefExp (function);
    SgFunctionSymbol *symbol = functionRefExp->get_symbol ();
    ROSE_ASSERT (symbol);
    SgFunctionDeclaration *functionDeclaration = symbol->get_declaration ();
    ROSE_ASSERT (functionDeclaration);
    const string functionName = functionDeclaration->get_name ().str ();
    if (functionName == "printf") {
        return VoEncoderPtr (new PrintfVoEncoder (synAttributes));
    } else if (functionName == "strcmp") {
        return VoEncoderPtr (new StrcmpVoEncoder (synAttributes));
    } else {
        throw "Unknown function!";
    }
}

void VirtualizationObfuscationProtector::print (SgNode *node) const {
    SgNode *parent = node->get_parent ();
    cerr << node << "[" << node->class_name () << "] -> ";
    if (parent) {
        cerr << "parent: " << parent << "[" << parent->class_name () << "] => ";
    } else {
        cerr << "parent: NULL => ";
    }
    cerr << "\n\t\t" << node->unparseToString () << endl;
}

