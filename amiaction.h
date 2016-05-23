#ifndef AmiACTION_H
#define AmiACTION_H
#include <QByteArray>
#include "amimsg.h"

class AmiMsg;
class ptt;

class AmiAction
{
public:
    explicit AmiAction(ptt* cl); // maybe construct the AmiMsg //
    virtual ~AmiAction(); // maybe destroy it //

    QByteArray getMsg();
private:
    void*   m_callee;
    AmiMsg m_msg;

};


#endif // AmiACTION_H
