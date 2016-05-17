#include "ptt.h"
#include <iostream>
#include <QDebug>

ptt::ptt(QObject *parent) : QObject(parent)
{
    m_button = new QPushButton;

    // keep in mind there are 2 signlas to handle choose which one //
    connect(m_button, SIGNAL(clicked(bool)),
            this, SLOT(hClick()));
    connect(m_button, SIGNAL(pressed()),
            this, SLOT(hClick()));

    m_button->setText("PTT");
    m_button->setMinimumHeight(200);
    m_button->setMinimumWidth(200);
    m_button->show();

}

void ptt::registerAmi(AMI* pami)
{
    m_ami = pami;
}


ptt::~ptt()
{

}

void ptt::hClick()
{
    // handle the click send the message //
    AmiAction *act = new AmiAction;
    doAction(act);

}


void ptt::doAction(AmiAction *action)
{

    // ami action will take an action using his msg ptr //
    m_ami->action(action->getMsg());
}
