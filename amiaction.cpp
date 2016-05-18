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
//    QByteArray s = m_msg.addAction("login").addMore("username:joro\n")
//            .addMore("secret:sopa123\n").submit();
    QByteArray s = m_msg.addAction("Ping").submit();
    return s;

}
