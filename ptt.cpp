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

    m_self = this; // this will point to the last one PTT4 in the case //
    m_act = new AmiAction(this);
    hlayout.addWidget(m_button);


}

void ptt::registerAmi(Ami* pAmi)
{
    if (pAmi != nullptr) {
        m_Ami = pAmi;
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
    // samo za ptt4 //
    while (ptt::m_self->m_button->isDown()) {
        ptt::m_self->doAction(ptt::m_self->m_act);
    }
}


void ptt::hReleased()
{
    // omit for now //
}


void ptt::hPress()
{
    // I want to hacve one pressed signal capturer //
    static phandle hndl(m_button);
    hndl.start();
}

void ptt::doAction(AmiAction *action)
{
    std::cout << "Callee: " << m_name.toStdString() << std::endl;

    // Ami action will take an action using his msg ptr //
    if (m_Ami != nullptr) {
        m_Ami->action(action->getMsg());
    }
}



