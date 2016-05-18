#ifndef PTT_H
#define PTT_H
#include <QPushButton>
#include <QObject>
#include "ami.h"
#include "amiinterface.h"
#include "amimsg.h"
#include "amiaction.h"

class AmiAction;

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

private:
    AmiAction m_act;
    AMI* m_ami; // reference to the AMI , I`ll talk with this //
    QPushButton* m_button; // pedal simulation //
};

#endif // PTT_H
