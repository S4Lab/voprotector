#include "rose.h"

#include "voencoder.h"

using namespace std;


VoEncoder::VoEncoder (int _offset, TypedValuePtr _typedValue) :
        offset (_offset), typedValue (_typedValue) {
    cerr << "VoEncoder(this=" << this << ", offset=" << offset << ")\n";
}

VoEncoder::~VoEncoder () {
}

void VoEncoder::setOffset (int _offset) {
    cerr << "offset is changing to " << _offset << " [this=" << this << "]" << endl;
    offset = _offset;
}

void VoEncoder::setType (TypedValuePtr _typedValue) {
    typedValue = _typedValue;
}

TypedValuePtr VoEncoder::getTypedValue () const {
    return typedValue;
}

