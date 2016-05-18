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
    // a bit UGLY but it`s a workspace test platform
    static int i=0;
    char id[12]={0};
    sprintf(id, "%d", i);
    i += 1;

    QByteArray s = m_msg.addAction("Ping")
            .addMore(QString("actionid:%1").arg(id)).addMore("\n")
            .submit();
    return s;

}
