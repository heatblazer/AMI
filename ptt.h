#ifndef PTT_H
#define PTT_H
#include <QThread>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QObject>

#include "ami.h"
#include "amiinterface.h"
#include "amimsg.h"
#include "amiaction.h"

class AmiAction;
class ptt;

// implplementing the AmiInterface //
class ptt : public QObject, public AmiInterface
{
    Q_OBJECT
public:
    explicit ptt(QObject* parent = nullptr);
    virtual ~ptt();

    virtual void doAction(AmiAction *action);
    void registerAmi(Ami* pAmi);    //for now register an outside Ami //


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

public:
    static QHBoxLayout hlayout;

private:

    Ami* m_Ami; // reference to the Ami , I`ll talk with this //
    AmiAction* m_act;

    /* test specific never met in RADIS2 */
    static ptt*        m_self;
    QPushButton* m_button; // pedal simulation //

    // test name //
    QString m_name;
    friend class phandle;

};

#endif // PTT_H
