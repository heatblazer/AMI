#ifndef AMI_H
#define AMI_H
#include <QObject>
class QTcpSocket;

class AMI : public QObject
{
    Q_OBJECT

    enum AmiState {
        AMI_CONNECTED,
        AMI_DISCONNECTED,
        AMI_CONNECTION_LOST,
        AMI_READY,
        AMI_LOGIN_OK,
        AMI_LOGIN_ERR,
        UNKNOWN
    };


public:
    explicit AMI(QObject* parent = nullptr);
    virtual ~AMI();
    void init(void);
    void action(const QString& act);


private:
    void login(const QString &uname, const QString &pass);

    // I`ll emit these so the client will know I am ready
signals:
    void loginSuccess();
    void loginError();

    void amiConnected();
    void amiDisconnected();

    void actionReady();
    void actionNotReady();

public slots:
    void hConnected();
    void hDisconnected();
    void hBytesWritten(qint64 bytes);
    void hReadyWrite();

private slots:
    void testAction(); // delete it
    void tryLogin();

// handle all changes in the state and route specific actions
    void route(void);


private:
    AmiState    m_state;
    QTcpSocket* m_socket;

};

#endif // AMI_H
