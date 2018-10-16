#include "rose.h"

#include "stringvoencoder.h"

using namespace std;


int StringVoEncoder::lastIndex = 0;

StringVoEncoder::StringVoEncoder (string _str) :
    VoEncoder (0),
    index (lastIndex++),
    str (_str) {
    cerr << "StringVoEncoder(index=" << index << ", str=" << str << ")\n";
}

int StringVoEncoder::getSize () const {
    return 9;
}

void StringVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "StringVoEncoder::encode\n";
    const int absoluteOffset = parentAbsoluteOffset + offset;
    stringstream ss;
    ss << "str" << index;
    SgVariableDeclaration *strDecl = SageBuilder::buildVariableDeclaration
        (ss.str (),
         SageBuilder::buildPointerType (SageBuilder::buildConstType (SageBuilder::buildCharType ())),
         SageBuilder::buildAssignInitializer (SageBuilder::buildStringVal (str)));
    SageInterface::appendStatement (strDecl, globalVariables);
    
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x11, "0x11")));
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
             (SageBuilder::buildConstType (SageBuilder::buildCharType ()))))),
          SageBuilder::buildVarRefExp (ss.str ())));
    SageInterface::appendStatement (strAssignment, init_func_body);
}

