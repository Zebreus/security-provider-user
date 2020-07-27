#include "democlient.h"

DemoClient::DemoClient(QObject *parent) : QObject(parent)
{
    connect(&webSocket, &QWebSocket::connected, this, &DemoClient::onConnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &DemoClient::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &DemoClient::onBinaryMessageReceived);
    connect(&webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &DemoClient::onError);
}

void DemoClient::login(const QString &token)
{
    this-> token = token;
    webSocket.open(url);
}

void DemoClient::setUrl(const QUrl &url)
{
    this->url = url;
}

void DemoClient::onBinaryMessageReceived(const QByteArray &message)
{
        onTextMessageReceived(QString::fromLatin1(message));
}

void DemoClient::onConnected()
{
    QJsonDocument doc;
    QJsonObject jsonRequest;
    jsonRequest["jsonrpc"] = "2.0";
    jsonRequest["id"] = 5;
    jsonRequest["method"] = "login";
    QJsonArray params;
    params.append(token);
    jsonRequest["params"] = params;
    doc.setObject(jsonRequest);
    QString message = doc.toJson(QJsonDocument::Compact);
    webSocket.sendTextMessage(message);
    qDebug() << "Sent: " << message;
}

void DemoClient::onError(QAbstractSocket::SocketError error)
{
    qDebug() << "Error";
}

void DemoClient::onTextMessageReceived(const QString &message)
{
    qDebug() << message;
    qDebug() << message;
    QJsonDocument document = QJsonDocument::fromJson(message.toLatin1());
    QJsonObject responseObject = document.object();
    QJsonValue idValue = responseObject.value("id");
    if(idValue.isDouble()){
        int id = idValue.toInt();
        QJsonValue tokenValue = responseObject.value("result");
        if(tokenValue.isBool()){
            qDebug() << "Got: " << tokenValue.toBool();
            emit response(tokenValue.toBool());
        }else{
            qDebug() << "Got no bool";
            emit error(PROTOCOL_ERROR);
        }
    }else{
        emit error(PROTOCOL_ERROR);
    }
}
