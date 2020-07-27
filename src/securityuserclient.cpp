#include "securityuserclient.h"

SecurityUserClient::SecurityUserClient(QObject *parent):
    QObject(parent), webSocket()
{
    connect(&webSocket, &QWebSocket::connected, this, &SecurityUserClient::onConnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &SecurityUserClient::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::binaryMessageReceived, this, &SecurityUserClient::onBinaryMessageReceived);
    connect(&webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &SecurityUserClient::onError);
}

void SecurityUserClient::obtainToken(const QString &username, const QString &password, QList<QString> claims)
{
    Request r;
    r.name = username;
    r.password = password;
    r.claims = claims;
    if(webSocket.isValid()){
        sendRequest(r, currentId++);
    }else{
        requests.insert(currentId++, r);
        qDebug("test");
    }
}

void SecurityUserClient::setUrl(const QUrl &url)
{
    this->url = url;
}

void SecurityUserClient::open()
{
    webSocket.open(url);
}

void SecurityUserClient::sendRequest(const SecurityUserClient::Request &request, int id)
{
    QJsonDocument doc;
    QJsonObject jsonRequest;
    jsonRequest["jsonrpc"] = "2.0";
    jsonRequest["id"] = id;
    jsonRequest["method"] = "getToken";
    QJsonArray params;
    params.append(request.name);
    params.append(request.password);
    params.append(QJsonArray::fromStringList(request.claims));
    jsonRequest["params"] = params;
    doc.setObject(jsonRequest);
    QString message = doc.toJson(QJsonDocument::Compact);
    webSocket.sendTextMessage(message);
    qDebug() << "Sent: " << message;
}

void SecurityUserClient::onConnected()
{
    qDebug("Connected");
    auto i = requests.constBegin();
    while(i != requests.constEnd()){
        sendRequest(i.value(), i.key());
        ++i;
    }
    requests.clear();
}

void SecurityUserClient::onError(QAbstractSocket::SocketError e)
{
    emit error(SOCKET_ERROR);
}

void SecurityUserClient::onBinaryMessageReceived(const QByteArray &message)
{
    onTextMessageReceived(QString::fromLatin1(message));
}

void SecurityUserClient::onTextMessageReceived(const QString& message)
{
    qDebug() << message;
    QJsonDocument document = QJsonDocument::fromJson(message.toLatin1());
    QJsonObject response = document.object();
    QJsonValue idValue = response.value("id");
    if(idValue.isDouble()){
        int id = idValue.toInt();
        QJsonValue tokenValue = response.value("result");
        if(tokenValue.isString()){
            emit gotToken(tokenValue.toString());
        }else{
            emit error(PROTOCOL_ERROR);
        }
    }else{
        emit error(PROTOCOL_ERROR);
    }

}
