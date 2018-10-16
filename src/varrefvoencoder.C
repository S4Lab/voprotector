#include "rose.h"

#include "varrefvoencoder.h"
#include "vardeclvoencoder.h"

using namespace std;


VarRefVoEncoder::VarRefVoEncoder (SgVarRefExp *varRef) : VoEncoder (0) {
    name = varRef->get_symbol ()->get_name ();
    isArgc = (name == "argc");
    if (isArgc) {
        name = "argcptr";
    }
    setType (TypedValue::instantiateTypeFromSageVarRef (varRef));
    cerr << "VarRefVoEncoder(name=" << name << ", type=" << typedValue->toString () << ")\n";
}

VarRefVoEncoder::VarRefVoEncoder (string _name, TypedValuePtr _type) :
        VoEncoder (0, _type),
        name (_name),
        isArgc (false) {
    cerr << "VarRefVoEncoder(isArgc=false, name=" << name << ", type=" << typedValue->toString () << ")\n";
}

int VarRefVoEncoder::getSize () const {
    return (isArgc ? 9 : 5);
}

void VarRefVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "VarRefVoEncoder::encode\n";
    if (isArgc) {
        encodeArgc (parentAbsoluteOffset, globalVariables, program_text, init_func_body);
    } else {
        encodeVarByOffset (parentAbsoluteOffset, globalVariables, program_text, init_func_body);
    }
}

string VarRefVoEncoder::getName () const {
    return name;
}

void VarRefVoEncoder::encodeVarByOffset (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    const int absoluteOffset = parentAbsoluteOffset + offset;
    const int encodedType = 0x06 + typedValue->getType ();
    stringstream ss;
    ss << "0x" << hex << uppercase << setw (2) << setfill ('0') << int32_t(encodedType & 0xFF);
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (encodedType, ss.str ())));
    const int relativeVarOffset = VarDeclVoEncoder::variableNameToAbsoluteOffset[name] - (absoluteOffset + 5);
    for (int i = 0; i < 4; ++i) {
        const char val = (reinterpret_cast<const char *> (&relativeVarOffset))[i];
        stringstream ss;
        ss << "'\\x" << hex << uppercase << setw (2) << setfill ('0') << int32_t(val & 0xFF) << "'";
        program_text->append_expression (SageBuilder::buildAssignInitializer
                (SageBuilder::buildCharVal_nfi (val, ss.str ())));
    }
}

void VarRefVoEncoder::encodeArgc (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    const int absoluteOffset = parentAbsoluteOffset + offset;
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x01, "0x01")));
    for (int i = 0; i < 8; ++i) {
        program_text->append_expression (SageBuilder::buildAssignInitializer
                (SageBuilder::buildCharVal_nfi (0xFF, "'\\xFF'")));
    }

    SgExprStatement *strAssignment = SageBuilder::buildExprStatement
        (SageBuilder::buildAssignOp 
         (SageBuilder::buildPointerDerefExp
          (SageBuilder::buildCastExp
           (SageBuilder::buildAddressOfOp
            (SageBuilder::buildPntrArrRefExp
             (SageBuilder::buildVarRefExp ("program"),
              SageBuilder::buildIntVal (absoluteOffset + 1))),
            SageBuilder::buildPointerType
            (SageBuilder::buildPointerType
             (SageBuilder::buildIntType ())))),
          SageBuilder::buildVarRefExp (name)));
    SageInterface::appendStatement (strAssignment, init_func_body);
}

