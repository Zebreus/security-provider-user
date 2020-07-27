#ifndef DEMOCLIENT_H
#define DEMOCLIENT_H

#include <QString>
#include <QObject>
#include <QWebSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTimer>



class DemoClient : public QObject
{
    Q_OBJECT

    QUrl url;
    QWebSocket webSocket;
    QString token;
public:
    enum Errors{
        SOCKET_ERROR,
        PROTOCOL_ERROR,
        AUTHENTICATION_ERROR
    };
    explicit DemoClient(QObject *parent = nullptr);
    void login(const QString& token);
    void setUrl(const QUrl &url);

signals:
    void response(bool success);
    void error(Errors code);

private Q_SLOTS:
    void onBinaryMessageReceived(const QByteArray &message);
    void onConnected();
    void onError(QAbstractSocket::SocketError error);
    void onTextMessageReceived(const QString& message);
};

#endif // DEMOCLIENT_H
