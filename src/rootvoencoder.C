#include "rose.h"

#include "rootvoencoder.h"

using namespace std;


RootVoEncoder::RootVoEncoder (SgGlobal *_globalScope, SgFunctionDeclaration *_mainDec,
    VoEncoderPtrsList _children) :
        SequenceVoEncoder (_children),
        globalScope (_globalScope),
        mainDec (_mainDec) {
    cerr << "RootVoEncoder()\n";
}
    
void RootVoEncoder::encode () const {
    cerr << "RootVoEncoder::encode\n";
    SgBasicBlock *globalVariables = SageBuilder::buildBasicBlock ();
    SgExprListExp *program_text = SageBuilder::buildExprListExp ();
    for (int i = 0; i < 8; ++i) {
        program_text->append_expression (SageBuilder::buildAssignInitializer
                (SageBuilder::buildCharVal_nfi (0xAB, "'\\xAB'")));
    }

    SgFunctionDeclaration *init_program_func = buildInitProgramFunction ();
    SgBasicBlock *init_func_body = init_program_func->get_definition()->get_body();

    SequenceVoEncoder::encode (8, globalVariables, program_text, init_func_body);

    SageInterface::appendStatement
        (SageBuilder::buildReturnStmt (SageBuilder::buildVarRefExp ("program")),
         init_func_body);

    replaceMain (mainDec, globalVariables, program_text, init_program_func);
}

void RootVoEncoder::replaceMain (SgFunctionDeclaration *mainDec,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgFunctionDeclaration *init_program_func) const {
    SgVariableDeclaration *program_text_var = SageBuilder::buildVariableDeclaration
        ("program_text",
         SageBuilder::buildArrayType (SageBuilder::buildConstType (SageBuilder::buildCharType ())),
         SageBuilder::buildAggregateInitializer (program_text));
    SgArrayType *array = SageBuilder::buildArrayType (SageBuilder::buildCharType ());
    array->set_index (SageBuilder::buildSizeOfOp (SageBuilder::buildVarRefExp ("program_text")));
    SgVariableDeclaration *program_var = SageBuilder::buildVariableDeclaration
        ("program", array);

    SageInterface::removeStatement (mainDec);

    SageInterface::appendStatementList (globalVariables->get_statements (), globalScope);
    SageInterface::appendStatement (program_text_var, globalScope);
    SageInterface::appendStatement (program_var, globalScope);
    SageInterface::appendStatement (init_program_func, globalScope);
}

SgFunctionDeclaration *RootVoEncoder::buildInitProgramFunction () const {
    SgInitializedName *argcptr_init_name = SageBuilder::buildInitializedName
        ("argcptr",
        SageBuilder::buildPointerType (SageBuilder::buildIntType ()));
    SgInitializedName *argv_init_name = SageBuilder::buildInitializedName
        ("argv",
        SageBuilder::buildArrayType (SageBuilder::buildPointerType (SageBuilder::buildCharType ())));
    SgFunctionParameterList *parameterList = SageBuilder::buildFunctionParameterList();
    SageInterface::appendArg (parameterList, argcptr_init_name);
    SageInterface::appendArg (parameterList, argv_init_name);

    SgFunctionDeclaration *init_program_func = SageBuilder::buildDefiningFunctionDeclaration
        ("init_program",
         SageBuilder::buildPointerType (SageBuilder::buildConstType (SageBuilder::buildCharType ())),
         parameterList,
         globalScope);

    SgBasicBlock *init_func_body = init_program_func->get_definition()->get_body();
    SgExprListExp *memcpy_parameters = SageBuilder::buildExprListExp ();
    memcpy_parameters->append_expression (SageBuilder::buildVarRefExp ("program"));
    memcpy_parameters->append_expression (SageBuilder::buildVarRefExp ("program_text"));
    memcpy_parameters->append_expression (SageBuilder::buildSizeOfOp (SageBuilder::buildVarRefExp ("program_text")));
    SgExprStatement *memcpy = SageBuilder::buildFunctionCallStmt
        ("memcpy",
        SageBuilder::buildPointerType (SageBuilder::buildVoidType ()),
        memcpy_parameters,
        init_func_body);
    SageInterface::appendStatement (memcpy, init_func_body);

    SgExprStatement *argvAssignment = SageBuilder::buildExprStatement
        (SageBuilder::buildAssignOp 
         (SageBuilder::buildPointerDerefExp
          (SageBuilder::buildCastExp
           (SageBuilder::buildAddressOfOp
            (SageBuilder::buildPntrArrRefExp
             (SageBuilder::buildVarRefExp ("program"),
              SageBuilder::buildIntVal (0))),
            SageBuilder::buildPointerType
            (SageBuilder::buildPointerType
             (SageBuilder::buildVoidType ())))),
          SageBuilder::buildVarRefExp ("argv")));
    SageInterface::appendStatement (argvAssignment, init_func_body);

    return init_program_func;
}

