#include "userbackend.h"

UserBackend::UserBackend(QObject *parent) : QObject(parent)
{
    m_providerUrl = "ws://localhost:9092";
    m_serverUrl = "ws://localhost:9093";
    connect(&client, &SecurityUserClient::gotToken, this, &UserBackend::gotToken);
    connect(&client, &SecurityUserClient::error, this, &UserBackend::providerError);
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
    client.setUrl(m_providerUrl);
    client.open();
    client.obtainToken(m_username,m_password,QList<QString>{"testclaim"});
}

void UserBackend::login()
{
    if(m_token == "dummytoken"){
        m_loggedIn = true;
    }else{
        m_loggedIn = false;
    }
    emit loggedInChanged(m_loggedIn);
}

void UserBackend::gotToken(QString token)
{
    m_token = token;
    emit tokenChanged(token);
}

void UserBackend::providerError(SecurityUserClient::Errors e)
{
    switch(e){
    case SecurityUserClient::Errors::SOCKET_ERROR:
        m_token = "Server error";
        break;
    case SecurityUserClient::Errors::PROTOCOL_ERROR:
        m_token = "Protocol error";
        break;
    case SecurityUserClient::Errors::AUTHENTICATION_ERROR:
        m_token = "Authetication error";
        break;
    }
    emit tokenChanged(m_token);
}
