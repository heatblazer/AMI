#ifndef AMIINTERFACE_H
#define AMIINTERFACE_H
#include "amiaction.h"

// I want you to implement it forcibly and never instante it //
class AmiInterface
{
public:
    AmiInterface();
    virtual ~AmiInterface() = 0;
    // as for newer C++ we can provide default body but we don`t want to
    virtual void doAction(AmiAction* aciton) = 0;

};


#endif // AMIINTERFACE_H
