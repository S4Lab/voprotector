#ifndef VO_ENCODER_H
#define VO_ENCODER_H

#include "typedvalue.h"

class VoEncoder;
typedef boost::shared_ptr<VoEncoder> VoEncoderPtr;
typedef std::vector<VoEncoderPtr> VoEncoderPtrsList;

class VoEncoder {
protected:
    int offset;
    TypedValuePtr typedValue;

    VoEncoder (int _offset, TypedValuePtr _typedValue = TypedValue::instantiateUnknownType ());
    virtual ~VoEncoder ();

public:
    void setOffset (int _offset);

    virtual int getSize () const = 0;
    virtual void encode (int parentAbsoluteOffset,
            SgBasicBlock *globalVariables,
            SgExprListExp *program_text,
            SgBasicBlock *init_func_body) const = 0;

    void setType (TypedValuePtr _typedValue);
    TypedValuePtr getTypedValue () const;
};

#endif
