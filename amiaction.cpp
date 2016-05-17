#include "amiaction.h"
#include "amimsg.h"
#include <QString>

AmiAction::AmiAction()
{

}

AmiAction::~AmiAction()
{

}

QString AmiAction::getMsg()
{
    QString s = m_msg->addAction("login").addMore("username:joro\n")
            .addMore("secret:sopa123\n").submit();
    return s;

}
