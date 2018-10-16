#include "rose.h"

#include "typedvalue.h"


using namespace std;


TypedValue::TypedValue (Type _type, TypedValuePtr _targetType) :
    type (_type), targetType (_targetType) {
}

TypedValue::Type TypedValue::getType () const {
    return type;
}

int TypedValue::getSize () const {
    switch (type) {
        case Char:
            return 1;
        case Int:
            return 4;
        case Pointer:
        case Unknown:
            return 8;
        default:
            throw "TypedValue::getSize (): Unknown size!";
    }
}

bool TypedValue::isPointer () const {
    return type == Pointer;
}

TypedValuePtr TypedValue::getDereferencedType () const {
    return targetType;
}

string TypedValue::toString () const {
    switch (type) {
        case Unknown:
            return "<unknown>";
        case Char:
            return "char";
        case Int:
            return "int";
        case Pointer:
            return targetType->toString () + "*";
        default:
            throw "TypedValue::toString () has an invalid type!";
    }
}

TypedValuePtr TypedValue::instantiateUnknownType () {
    return TypedValuePtr (new TypedValue (Unknown));
}

TypedValuePtr TypedValue::instantiateCharType () {
    return TypedValuePtr (new TypedValue (Char));
}

TypedValuePtr TypedValue::instantiateIntType () {
    return TypedValuePtr (new TypedValue (Int));
}

TypedValuePtr TypedValue::instantiatePointerType (TypedValuePtr targetType) {
    return TypedValuePtr (new TypedValue (Pointer, targetType));
}

TypedValuePtr TypedValue::instantiateTypeFromSageVarRef (SgVarRefExp *var) {
    return TypedValue::instantiateTypeFromSageType (var->get_type ());
}

TypedValuePtr TypedValue::instantiateTypeFromSageType (SgType *t) {
    if (SgModifierType *modType = isSgModifierType (t)) {
        t = modType->get_base_type ();
    }
    switch (t->variantT ()) {
        case V_SgPointerType:
            return TypedValue::instantiatePointerType
                (TypedValue::instantiateTypeFromSageType (isSgPointerType (t)->get_base_type ()));
        case V_SgArrayType:
            return TypedValue::instantiatePointerType
                (TypedValue::instantiateTypeFromSageType (isSgArrayType (t)->get_base_type ()));

        case V_SgTypeChar:
        case V_SgTypeSignedChar:
        case V_SgTypeUnsignedChar:
            return TypedValue::instantiateCharType ();

        case V_SgTypeShort:
        case V_SgTypeSignedShort:
        case V_SgTypeUnsignedShort:
        case V_SgTypeInt:
        case V_SgTypeSignedInt:
        case V_SgTypeUnsignedInt:
        case V_SgTypeLong:
        case V_SgTypeSignedLong:
        case V_SgTypeUnsignedLong:
            return TypedValue::instantiateIntType ();

        default:
            cerr << "t->variantT (): " << t->variantT () << endl;
            cerr << "get_type_name (t): " << get_type_name (t) << endl;
            return TypedValue::instantiateUnknownType ();
    }
}

