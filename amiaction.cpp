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
    QByteArray s = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s10 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s9 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s8 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s7 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s6 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s5 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s4 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s3 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s2 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    QByteArray s1 = m_msg.addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();


    return s;

}
