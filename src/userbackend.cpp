#include "userbackend.h"

UserBackend::UserBackend(QObject *parent) : QObject(parent)
{

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
    if(m_username != "" && m_password != ""){
        m_token = "dummytoken";
    }else{
        m_token = "invalid";
    }
    emit tokenChanged(m_token);
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
