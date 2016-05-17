#ifndef AMIACTION_H
#define AMIACTION_H
#include <QByteArray>
#include "amimsg.h"

class AmiMsg;

class AmiAction
{
public:
    explicit AmiAction(); // maybe construct the AmiMsg //
    virtual ~AmiAction(); // maybe destroy it //

    QByteArray getMsg();
private:
    AmiMsg m_msg;

};


#endif // AMIACTION_H
