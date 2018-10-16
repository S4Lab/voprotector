#include "rose.h"

#include "intvoencoder.h"

using namespace std;


IntVoEncoder::IntVoEncoder (int32_t _value) :
    VoEncoder (0, TypedValue::instantiateIntType ()),
    value (_value) {
}

int IntVoEncoder::getSize () const {
    return 5;
}

void IntVoEncoder::encode (int parentAbsoluteOffset,
        SgBasicBlock *globalVariables,
        SgExprListExp *program_text,
        SgBasicBlock *init_func_body) const {
    cerr << "IntVoEncoder::encode\n";
    program_text->append_expression (SageBuilder::buildAssignInitializer
            (SageBuilder::buildCharVal_nfi (0x02, "0x02")));
    for (int i = 0; i < 4; ++i) {
        const char val = (reinterpret_cast<const char *> (&value))[i];
        stringstream ss;
        ss << "'\\x" << hex << uppercase << setw (2) << setfill ('0') << int32_t(val & 0xFF) << "'";
        program_text->append_expression (SageBuilder::buildAssignInitializer
                (SageBuilder::buildCharVal_nfi (val, ss.str ())));
    }
}

