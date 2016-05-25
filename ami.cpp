#include "ami.h"

#include <QTcpSocket>

#include <iostream>
#include <stdio.h> // for fprintf //


Ami::Ami(QObject *parent) :
    QObject(parent), m_state(AmiState::Ami_DISCONNECTED)
{

}


Ami::~Ami()
{
    if (m_socket != nullptr) {
        delete m_socket;
    }
}


//!
//! \brief Ami::init, initializes socket and connections between objects
//! also, returns a value, and emits a signal
//! \param pResult return of the created QTcpSocket (1-OK) (0-FAIL)
//! NOTE :this is NOT FORBIDEN BY <C/C++ MISRA>
//!
void Ami::init(int *pResult)
{
    // I am interested IF m_socket was created, I don`t want asserts with    //
    // tryung to access not created socket                                   //
    // I will create the socket in the init since constructor can`t return a //
    // value, and I might need to return error if socket can`t be allocated  //
    static bool is_init = false;
    if (!is_init) {
        is_init = true; // second init guard;

        m_socket = new QTcpSocket(this);

        if (m_socket != nullptr){
            *pResult = 1;
        } else {
            *pResult = 0;
        }

        // handle socket signals then route the Ami //
        connect(m_socket, SIGNAL(connected()),
                this, SLOT(hConnected()));

        connect(m_socket, SIGNAL(disconnected()),
                this, SLOT(hDisconnected()));

        connect(m_socket, SIGNAL(bytesWritten(qint64)),
                this, SLOT(hBytesWritten(qint64)));

        connect(m_socket, SIGNAL(readyRead()),
                this, SLOT(hReadyWrite()));

        // connect to the routing function also
        connect(this, SIGNAL(AmiStateChanged(AmiState)),
                this, SLOT(route()));

        // jump to the routing function //
        emit AmiStateChanged(m_state);
    }
    // fall here if secont call to init
}

void Ami::testAction()
{
    m_socket->write("Action: ListCommands\n\n");
}

void Ami::tryLogin()
{
    login("goro", "sopa123"); // тествам грешен login //
   //login("joro", "sopa123");
}


void Ami::hConnected()
{
    m_state = AmiState::Ami_CONNECTED;
    emit AmiStateChanged(m_state);
}


void Ami::hDisconnected()
{
    m_state = AmiState::Ami_DISCONNECTED;
    emit AmiStateChanged(m_state);
}


void Ami::hBytesWritten(qint64 bytes)
{
    std::cout  << "Bytes written: " << bytes;
    if(bytes > 0){
        m_state = AmiState::Ami_READY;
    } else {
        m_state = AmiState::Ami_NOT_READY;
    }
    emit AmiStateChanged(m_state);
}

// maybe emit or change state //
void Ami::hReadyWrite()
{
    QString s;
    m_state = AmiState::Ami_NOT_READY;
    if (m_socket->canReadLine()) {
        // read all //
        // or if needed read line by line depends what do we need //
        s = QString(m_socket->readAll().simplified());
        printf("%s\n", s.toLocal8Bit().constData());
        m_state = AmiState::Ami_READY;
    }
    // else Ami is not ready //

    emit AmiStateChanged(m_state);
}

//!
//! \brief take Ami action
//! \param string or uri taking the action
//!
void Ami::action(const QString &act)
{
    qint64 bytes = m_socket->write(act.toLocal8Bit());
    if(bytes <= 0) {
        m_state = AmiState::Ami_NOT_READY;
    } else {
        m_state = AmiState::Ami_READY;
    }

    emit AmiStateChanged(m_state);
}


//!
//! \brief Handle all Ami states and route them to the approp functions
//!
void Ami::route(void)
{
    switch (m_state)
    {
    case AmiState::Ami_LOGIN_OK:
        std::cout << "LOGGED IN\n";
        break;

    case AmiState::Ami_LOGIN_FAILED:
        std::cout << "NOT LOGGED IN\n";
        // какво да правим тука??? //
        // да пробваме пак? //
        tryLogin();
        break;

    case AmiState::Ami_CONNECTED:
        std::cout << "Ami CONNECTED\n";
        // try login
        tryLogin();
        break;

    case AmiState::Ami_CONNECTION_LOST:
        std::cout << "Ami CONNECTION LOST\n";
        // try to reconnect //
        m_socket->connectToHost("192.168.32.89", 5038);
        break;

    case AmiState::Ami_READY:
        std::cout << "Ami READY\n";
        // ready to send actions
        break;

    case AmiState::Ami_NOT_READY:
        std::cout << "Ami NOT READY\n";
        break;

    case AmiState::Ami_DISCONNECTED:
        std::cout << "Ami DISCONNECTED\n";
        // try to connect  //
    default:
        m_socket->connectToHost("192.168.32.89", 5038);
        break;
    }
}


void Ami::login(const QString& uname, const QString& pass)
{
    QString login_str = QString("Action: Login\nUsername: %1\nSecret: %2\n\n")
            .arg(uname).arg(pass);

    qint64 res = m_socket->write(login_str.toLocal8Bit());
    // I can`t be logged with -1 or less bytes than requested to be written //
    if ((res < 0) || (res < login_str.length())) {
        // the command will be error
        m_state = AmiState::Ami_LOGIN_FAILED;
    } else {
        m_state = AmiState::Ami_LOGIN_OK;
    }

    emit AmiStateChanged(m_state);
}


