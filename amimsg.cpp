#include "amimsg.h"


AmiMsg::~AmiMsg()
{

}


AmiMsg::AmiMsg()
{

}



AmiMsg& AmiMsg::addAction(const QString &act)
{
    m_msgForAmi.append(act);
    m_msgForAmi.append("\n");
    return *this;
}


AmiMsg& AmiMsg::addEvent(const QString &ev)
{
    m_msgForAmi.append(ev);
    m_msgForAmi.append("\n");
    return *this;
}


AmiMsg& AmiMsg::addResponse(const QString &resp)
{
    m_msgForAmi.append(resp);
    m_msgForAmi.append("\n");
    return *this;
}


QString AmiMsg::build()
{
    return m_msgForAmi;
}
