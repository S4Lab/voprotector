#include "rose.h"

#include "typedvalue.h"
#include "voencoder.h"
#include "sequencevoencoder.h"
#include "minusvoencoder.h"
#include "intvoencoder.h"
#include "returnvoencoder.h"
#include "jumpvoencoder.h"
#include "conditionvoencoder.h"
#include "ifthenelsevoencoder.h"
#include "pntrderefvoencoder.h"
#include "addressofvoencoder.h"
#include "assignvoencoder.h"
#include "varrefvoencoder.h"
#include "vardeclvoencoder.h"
#include "printfvoencoder.h"
#include "rootvoencoder.h"
#include "virtualizationobfuscationprotector.h"

#include <iostream>
#include <iomanip>
#include <map>

using namespace std;


int main (int argc, char *argv[]) {
    ROSE_INITIALIZE;

    SgProject* project = frontend(argc,argv);
    ROSE_ASSERT(project != NULL);

    VarDeclVoEncoder::variableNameToAbsoluteOffset.insert (make_pair ("argv", 0));

    VirtualizationObfuscationProtector voTraversal;
    try {
        voTraversal.traverse (project);
    } catch (const VoEncoderPtr &voep) {
        RootVoEncoder *rvoe = dynamic_cast<RootVoEncoder *> (voep.get ());
        ROSE_ASSERT (rvoe != NULL);
        rvoe->encode ();
    } catch (const char *err_msg) {
        cerr << "Exception thrown: " << err_msg << endl;
        return -1;
    }
    SgGlobal *globalScope = SageInterface::getFirstGlobalScope (project);
    SageInterface::insertHeader ("string.h", PreprocessingInfo::after, true, globalScope);

    return backend (project);
}

