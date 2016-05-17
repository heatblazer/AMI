#include "amiaction.h"
#include "amimsg.h"
#include <QString>

AmiAction::AmiAction()
{

}

AmiAction::~AmiAction()
{

}

QByteArray AmiAction::getMsg()
{
    QByteArray s = m_msg->addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s1 = m_msg->addEvent("error").addMore("dasdsadas")
            .addMore("231232132132").addMore("43reddsfdsf").submit();
    QByteArray s2 = m_msg->addResponse("hui")
            .addMore("1212121").addMore("434343432432")
            .addMore("dsadsadsadsadsad").addMore("dsadsadsa")
            .addEvent("!!!!!").submit();


    return s;

}
