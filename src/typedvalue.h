#ifndef TYPED_VALUE_H
#define TYPED_VALUE_H


class TypedValue;
typedef boost::shared_ptr<const TypedValue> TypedValuePtr;

class TypedValue {
public:
    enum Type {
        Unknown = 0,
        Char = 1,
        Int = 2,
        Pointer = 3,
    };

private:
    const Type type;
    const TypedValuePtr targetType;

    TypedValue (Type _type, TypedValuePtr _targetType = TypedValuePtr ());

public:
    Type getType () const;

    int getSize () const;

    bool isPointer () const;

    TypedValuePtr getDereferencedType () const;

    std::string toString () const;

    static TypedValuePtr instantiateUnknownType ();
    static TypedValuePtr instantiateCharType ();
    static TypedValuePtr instantiateIntType ();
    static TypedValuePtr instantiatePointerType (TypedValuePtr targetType);
    static TypedValuePtr instantiateTypeFromSageVarRef (SgVarRefExp *var);
    static TypedValuePtr instantiateTypeFromSageType (SgType *t);
};

#endif
