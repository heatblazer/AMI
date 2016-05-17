#include "amimsg.h"


AmiMsg::~AmiMsg()
{

}


AmiMsg::AmiMsg()
{

}


AmiMsg& AmiMsg::addAction(const QString &act)
{
    m_msgForAmi.append("Action:");
    m_msgForAmi.append(act);
    m_msgForAmi.append("\n");
    return *this;
}


AmiMsg& AmiMsg::addEvent(const QString &ev)
{
    m_msgForAmi.append("Event:");
    m_msgForAmi.append(ev);
    m_msgForAmi.append("\n");
    return *this;
}


AmiMsg& AmiMsg::addResponse(const QString &resp)
{
    m_msgForAmi.append("Response:");
    m_msgForAmi.append(resp);
    m_msgForAmi.append("\n");
    return *this;
}


//!
//! \brief AmiMsg::addMore
//! \param append more text. You are responsible for the NEWLINE!!!
//! \return AmiMsg for building
//!
AmiMsg &AmiMsg::addMore(const QString &app)
{
    m_msgForAmi.append(app);
    return *this;
}


QString AmiMsg::submit()
{
    m_msgForAmi.append("\n"); // terminal symbol //
    return m_msgForAmi;
}
