#ifndef AMIMSG_H
#define AMIMSG_H
#include <QString>
class AmiClient;

class AmiMsg
{
// we care for these one for now
    enum MsgType
    {
        EVENT,
        ACTION,
        RESPONSE
    };

    enum ArrSize{MAX=10};
public:
    explicit AmiMsg();
    virtual ~AmiMsg();

    AmiMsg& addEvent(const QString& ev);
    AmiMsg& addAction(const QString& act);
    AmiMsg& addResponse(const QString& resp);
    AmiMsg &addMore(const QString& app);

    QByteArray submit(void);

private:
    // on call, call my function //
    QString m_command;
    // who called me? //
    AmiClient* m_callee;

};

#endif // AMIMSG_H
