#ifndef AMIMSG_H
#define AMIMSG_H
#include <QString>
#include <QList>

class AmiClient;
#define MAX 10
class AmiMsg
{
// we care for these one for now
    enum MsgType
    {
        EVENT,
        ACTION,
        RESPONSE
    };

public:
    explicit AmiMsg();
    virtual ~AmiMsg();

    AmiMsg& addEvent(const QString &ev);
    AmiMsg& addAction(const QString &act);
    AmiMsg& addResponse(const QString &resp);
    AmiMsg &addMore(const QString &app);

    QByteArray submit(void);

private:
    // on call, call my function //
    char     m_msgForAmi[MAX][128];
    int      m_next;
    // who called me? //
    AmiClient* m_callee;

};

#endif // AMIMSG_H
