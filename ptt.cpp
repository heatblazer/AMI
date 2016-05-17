#include "ptt.h"
#include <iostream>
#include <QDebug>

ptt::ptt(QObject *parent) : QObject(parent)
{
    m_button = new QPushButton;
    connect(m_button, SIGNAL(clicked(bool)),
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

}


void ptt::doAction(AmiAction *aciton)
{

}
