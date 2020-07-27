#ifndef SECURITYUSERCLIENT_H
#define SECURITYUSERCLIENT_H

#include <QString>
#include <QObject>
#include <QWebSocket>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTimer>



class SecurityUserClient : public QObject
{
    Q_OBJECT

    struct Request{
        QString name;
        QString password;
        QList<QString> claims;
    };

    QUrl url;
    QWebSocket webSocket;
    QMap<int, Request> requests;
    int currentId = 0;

public:
    enum Errors{
        SOCKET_ERROR,
        PROTOCOL_ERROR,
        AUTHENTICATION_ERROR
    };
    explicit SecurityUserClient(QObject *parent = nullptr);
    void obtainToken(const QString& username, const QString& password, QList<QString> claims);
    void setUrl(const QUrl &url);
    void open();

signals:
    void gotToken(QString token);
    void error(Errors code);


private:
    void sendRequest(const Request& r, int i);
private Q_SLOTS:
    void onBinaryMessageReceived(const QByteArray &message);
    void onConnected();
    void onError(QAbstractSocket::SocketError error);
    void onTextMessageReceived(const QString& message);
};

#endif // SECURITYUSERCLIENT_H
