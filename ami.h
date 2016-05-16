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

signals:
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
