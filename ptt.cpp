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
            this, SLOT(hPress()));

    m_button->setText("PTT");
    m_button->setMinimumHeight(200);
    m_button->setMinimumWidth(200);
    m_button->show();

}

void ptt::registerAmi(AMI* pami)
{
    if (pami != nullptr) {
        m_ami = pami;
    }
}


ptt::~ptt()
{

}

void ptt::hClick()
{
    // handle the click send the message //
    doAction(&m_act);

}


ptt::phandle::phandle(QPushButton *bhndl)
{
    pBtn = bhndl;
}

void ptt::phandle::run()
{
    while (pBtn->isDown()) {
        std::cout << "HANDLE BUTTON DOWN" << std::endl;
    }
}

void ptt::hPress()
{
    // don`t handle the hold button //
    static phandle ph(m_button);
    ph.start();
}

void ptt::doAction(AmiAction *action)
{

    // ami action will take an action using his msg ptr //
    if (m_ami != nullptr) {
        m_ami->action(action->getMsg());
    }
}



