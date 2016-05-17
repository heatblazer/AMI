#include "amimsg.h"


AmiMsg::~AmiMsg()
{

}


AmiMsg::AmiMsg() : m_next(0)
{
    for(int i=0; i < MAX; i++){
        memset(m_msgForAmi[i], 0, 128);

    }
    m_next = 0;
}


AmiMsg& AmiMsg::addAction(const QString &act)
{
    sprintf(m_msgForAmi[m_next], "Action:%s\n", act.toLocal8Bit().constData());
    m_next++;
    return *this;
}


AmiMsg& AmiMsg::addEvent(const QString &ev)
{
    sprintf(m_msgForAmi[m_next], "Event:%s\n", ev.toLocal8Bit().constData());
    m_next++;
    return *this;
}


AmiMsg& AmiMsg::addResponse(const QString &resp)
{
    sprintf(m_msgForAmi[m_next], "Response:%s\n", resp.toLocal8Bit().constData());
    m_next++;
    return *this;
}


//!
//! \brief AmiMsg::addMore
//! \param append more text. You are responsible for the NEWLINE!!!
//! \return AmiMsg for building
//!
AmiMsg &AmiMsg::addMore(const QString &app)
{
    sprintf(m_msgForAmi[m_next], "%s", app.toLocal8Bit().constData());
    m_next++;

    return *this;
}


QByteArray AmiMsg::submit()
{
    QString s;
    for(int i=0; i < m_next; i++) {
        s.append(m_msgForAmi[i]);
        memset(m_msgForAmi[i], 0, 128);
    }
    s.append("\n");
    m_next=0;
    return s.toLocal8Bit();

}
