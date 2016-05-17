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

public:
    explicit AmiMsg();
    virtual ~AmiMsg();

    AmiMsg& addEvent(const QString& ev);
    AmiMsg& addAction(const QString& act);
    AmiMsg& addResponse(const QString& resp);

    QString build(void);

private:
    // on call, call my function //
    QString     m_msgForAmi;

    AmiClient* m_callee; // who called me? //



};

#endif // AMIMSG_H
