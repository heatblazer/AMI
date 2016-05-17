#ifndef AMIINTERFACE_H
#define AMIINTERFACE_H

class AmiAction;

class AmiInterface
{
    AmiInterface();
    virtual ~AmiInterface() = 0;

    // as for newer C++ we can provide default body but we don`t want to
    virtual doAction(AmiAction* aciton) = 0;

};


#endif // AMIINTERFACE_H
