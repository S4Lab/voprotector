#ifndef STRING_VO_ENCODER_H
#define STRING_VO_ENCODER_H

#include "voencoder.h"


class StringVoEncoder : public VoEncoder {
private:
    static int lastIndex;

    const int index;
    std::string str;

public:
    StringVoEncoder (std::string _str);

    virtual int getSize () const;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const;
};

#endif
