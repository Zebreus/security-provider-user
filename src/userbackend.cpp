#include "userbackend.h"

UserBackend::UserBackend(QObject *parent) : QObject(parent)
{
    m_providerUrl = "ws://localhost:9092";
    m_serverUrl = "ws://localhost:9093";
    m_loggedIn = false;
    connect(&client, &securityprovider::Client::gotToken, this, &UserBackend::gotToken);
    connect(&client, &securityprovider::Client::error, this, &UserBackend::providerError);
    connect(&demoClient, &DemoClient::response, this, &UserBackend::loginStatus);
}

QString UserBackend::getUsername() const
{
    return m_username;
}

QString UserBackend::getPassword() const
{
    return m_password;
}

QString UserBackend::getProviderUrl() const
{
    return m_providerUrl;
}

QString UserBackend::getServerUrl() const
{
    return m_serverUrl;
}

QString UserBackend::getToken() const
{
    return m_token;
}

bool UserBackend::getLoggedIn() const
{
    return m_loggedIn;
}

void UserBackend::setUsername(QString username)
{
    if (m_username == username)
        return;

    m_username = username;
    emit usernameChanged(m_username);
}

void UserBackend::setPassword(QString password)
{
    if (m_password == password)
        return;

    m_password = password;
    emit passwordChanged(m_password);
}

void UserBackend::setProviderUrl(QString providerUrl)
{
    if (m_providerUrl == providerUrl)
        return;

    m_providerUrl = providerUrl;
    emit providerUrlChanged(m_providerUrl);
}

void UserBackend::setServerUrl(QString serverUrl)
{
    if (m_serverUrl == serverUrl)
        return;

    m_serverUrl = serverUrl;
    emit serverUrlChanged(m_serverUrl);
}

void UserBackend::setLoggedIn(bool loggedIn)
{
    if (m_loggedIn == loggedIn)
        return;

    m_loggedIn = loggedIn;
    emit loggedInChanged(m_loggedIn);
}

void UserBackend::obtainToken()
{
    client.getToken(m_username,m_password,QList<QString>{"testClaim"});
    client.open(m_providerUrl);
}

void UserBackend::login()
{
    demoClient.setUrl(m_serverUrl);
    demoClient.login(m_token);
}

void UserBackend::gotToken(QString token)
{
    m_token = token;
    emit tokenChanged(token);
}

void UserBackend::providerError(securityprovider::Client::Error e)
{
    switch(e){
    case securityprovider::Client::Error::SOCKET_ERROR:
        m_token = "Server error";
        break;
    case securityprovider::Client::Error::UNEXPECTED_MESSAGE:
        m_token = "Unexpected message";
        break;
    case securityprovider::Client::Error::INVALID_RESPONSE:
        m_token = "Invalid response";
        break;
    case securityprovider::Client::Error::SERVER_ERROR:
        m_token = "Server Error";
        break;
    }
    emit tokenChanged(m_token);
}

void UserBackend::loginStatus(bool status)
{
    m_loggedIn = status;
    emit loggedInChanged(status);
}
