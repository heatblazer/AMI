#include "amimsg.h"


int AmiMsg::m_next = 0;

AmiMsg::~AmiMsg()
{

}


AmiMsg::AmiMsg()
{
    for(int i=0; i < ArrSize::MAX; i++){
        memset(m_msgForAmi[i], 0, 128);

    }
    m_next = 0;
}


AmiMsg& AmiMsg::addAction(const char* act)
{
    sprintf(m_msgForAmi[m_next], "Action:%s\n", act);
    m_next++;
    return *this;
}


AmiMsg& AmiMsg::addEvent(const char* ev)
{
    sprintf(m_msgForAmi[m_next], "Event:%s\n", ev);
    m_next++;
    return *this;
}


AmiMsg& AmiMsg::addResponse(const char* resp)
{
    sprintf(m_msgForAmi[m_next], "Response:%s\n", resp);
    m_next++;
    return *this;
}


//!
//! \brief AmiMsg::addMore
//! \param append more text. You are responsible for the NEWLINE!!!
//! \return AmiMsg for building
//!
AmiMsg &AmiMsg::addMore(const char* app)
{
    sprintf(m_msgForAmi[m_next], "%s", app);
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
