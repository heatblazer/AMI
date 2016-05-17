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

    AmiMsg& addEvent(const char* ev);
    AmiMsg& addAction(const char* act);
    AmiMsg& addResponse(const char* resp);
    AmiMsg &addMore(const char* app);

    QByteArray submit(void);

private:
    // on call, call my function //
    char     m_msgForAmi[ArrSize::MAX][128];
    static int      m_next;
    // who called me? //
    AmiClient* m_callee;

};

#endif // AMIMSG_H
