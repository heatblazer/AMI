#include "ptt.h"
#include <iostream>
#include <QDebug>


ptt*    ptt::m_self =  nullptr;

QHBoxLayout ptt::hlayout;



ptt::ptt(QObject *parent) : QObject(parent)
{
    static int pttid=0;
    static char pttname[8]={0};
    // NOT MISRA !!!
    sprintf(pttname, "PTT%d", ++pttid);
    m_name = QString(pttname);

    m_button = new QPushButton;

    // keep in mind there are 2 signlas to handle choose which one //
    connect(m_button, SIGNAL(clicked(bool)),
            this, SLOT(hClick()));
    connect(m_button, SIGNAL(pressed()),
            this, SLOT(hPress()));
    connect(m_button, SIGNAL(released()),
            this, SLOT(hReleased()));

    m_button->setText(pttname);
    m_button->setMinimumHeight(200);
    m_button->setMinimumWidth(200);

    m_self = this;
    m_act = new AmiAction(this);
    hlayout.addWidget(m_button);


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
    doAction(m_act);

}


ptt::phandle::phandle(QPushButton *bhndl)
{
    pBtn = bhndl;
}

void ptt::phandle::run()
{

    while (ptt::m_self->m_button->isDown()) {
       // std::cout << "HANDLE BUTTON DOWN" << std::endl;
       // ptt::m_self->doAction(&ptt::m_self->m_act);
    }
}


void ptt::hReleased()
{

}

void ptt::hPress()
{
    // don`t handle the hold button //
    static phandle ph(m_button);
    ph.start();
}

void ptt::doAction(AmiAction *action)
{
    std::cout << "Callee: " << m_name.toStdString() << std::endl;

    // ami action will take an action using his msg ptr //
    if (m_ami != nullptr) {
        m_ami->action(action->getMsg());
    }
}



