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
    void init();
    void action(const QString& act);

    // I`ll emit these so the client will know I am ready
signals:
    void actionReady();
    void actionNotReady();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(quint64 bytes);
    void readyRead();
private slots:
private:
    QTcpSocket* m_socket;

};

#endif // AMI_H
