#ifndef AMI_H
#define AMI_H
#include <QObject>
class QTcpSocket;

class AMI : public QObject
{
    Q_OBJECT

public:
    explicit AMI(QObject* parent = nullptr);
    virtual ~AMI();
    void init(void);
    void action(const QString& act);

private:

    void route(void);

    // I`ll emit these so the client will know I am ready
signals:
    void actionReady();
    void actionNotReady();

public slots:
    void hConnected();
    void hDisconnected();
    void hBytesWritten(quint64 bytes);
    void hReadyWrite();
private slots:
private:
    QTcpSocket* m_socket;

};

#endif // AMI_H
