#ifndef PTT_H
#define PTT_H
#include <QThread>
#include <QPushButton>
#include <QObject>
#include "ami.h"
#include "amiinterface.h"
#include "amimsg.h"
#include "amiaction.h"

class AmiAction;
class ptt;

class ptt : public QObject, public AmiInterface
{
    Q_OBJECT
public:
    explicit ptt(QObject* parent = nullptr);
    virtual ~ptt();

    virtual void doAction(AmiAction *action);
    void registerAmi(AMI* pami);    //for now register an outside ami //


signals:

private slots:
    void hClick(void);
    void hPress(void);
    void hReleased(void);
private:

    class phandle : public QThread
    {
    public:
        explicit phandle(QPushButton* bhndl);
    private:
        void run();
        QPushButton* pBtn;
        friend class ptt;
    };

private:

    AMI* m_ami; // reference to the AMI , I`ll talk with this //
    AmiAction m_act;

    /* test specific never met in RADIS2 */
    static ptt*        m_self;
    QPushButton* m_button; // pedal simulation //
    friend class phandle;

};

#endif // PTT_H
