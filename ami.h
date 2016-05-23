#ifndef Ami_H
#define Ami_H
#include <QObject>
class QTcpSocket;

class Ami : public QObject
{
    Q_OBJECT

    enum AmiState {
        Ami_CONNECTED,
        Ami_DISCONNECTED,
        Ami_CONNECTION_LOST,
        Ami_READY,
        Ami_NOT_READY,
        Ami_LOGIN_OK,
        Ami_LOGIN_FAILED,
        UNKNOWN // кандидат за премахване //
    };


public:
    explicit Ami(QObject* parent = nullptr);
    virtual ~Ami();
    void init(int *pResult);
    void action(const QString& act);


private:
    //! ясно е, че е логин
    //! \brief login
    //! \param username
    //! \param password
    //!
    void login(const QString &uname, const QString &pass);

    // I`ll emit these so the client will know I am ready
signals:

    void AmiStateChanged(AmiState state);

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

#endif // Ami_H
