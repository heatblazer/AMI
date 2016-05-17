#include "amimsg.h"


AmiMsg::AmiMsg()
{

}


AmiMsg::~AmiMsg()
{

}



AmiMsg& AmiMsg::addAction(const QString& act)
{
    char s[128]={0};
    sprintf(s, "Action:%s\n", act.toLocal8Bit().constData());
    m_command.append(s);

    return *this;
}


AmiMsg& AmiMsg::addEvent(const QString &ev)
{
    char s[128];
    sprintf(s, "Event:%s\n", ev.toLocal8Bit().constData());
    m_command.append(s);
    return *this;
}


AmiMsg& AmiMsg::addResponse(const QString& resp)
{
    char s[128]={0};
    sprintf(s, "Response:%s\n", resp.toLocal8Bit().constData());
    m_command.append(s);

    return *this;
}


//!
//! \brief AmiMsg::addMore
//! \param append more text. You are responsible for the NEWLINE!!!
//! \return AmiMsg for building
//!
AmiMsg &AmiMsg::addMore(const QString& app)
{
    char s[128]={0};
    sprintf(s, "%s", app.toLocal8Bit().constData());
    m_command.append(s);

    return *this;
}


QByteArray AmiMsg::submit()
{
    m_command.append("\n");
    QByteArray ba = m_command.toLocal8Bit();
    m_command.clear();
    return ba;
}

