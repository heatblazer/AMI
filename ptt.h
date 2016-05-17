#ifndef PTT_H
#define PTT_H
#include <QPushButton>
#include <QObject>
#include "ami.h"
#include "amiinterface.h"
#include "amimsg.h"

class AmiAction;

class ptt : public QObject, public AmiInterface
{
    Q_OBJECT
public:
    explicit ptt(QObject* parent = nullptr);
    void registerAmi(AMI* pami);

    virtual ~ptt();

    virtual doAction(AmiAction *aciton);

signals:

private slots:
    void hClick(void);

private:
    AMI* m_ami; // reference to the AMI , I`ll talk with this //
    QPushButton* m_button; // pedal simulation //
};

#endif // PTT_H
