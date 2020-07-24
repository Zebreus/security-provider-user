#ifndef USERBACKEND_H
#define USERBACKEND_H

#include <QObject>
#include <QString>

class UserBackend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString providerUrl READ getProviderUrl WRITE setProviderUrl NOTIFY providerUrlChanged)
    Q_PROPERTY(QString serverUrl READ getServerUrl WRITE setServerUrl NOTIFY serverUrlChanged)
    Q_PROPERTY(QString token READ getToken NOTIFY tokenChanged)
    Q_PROPERTY(bool loggedIn READ getLoggedIn WRITE setLoggedIn NOTIFY loggedInChanged)

    QString m_username;
    QString m_password;
    QString m_providerUrl;
    QString m_serverUrl;
    QString m_token;
    bool m_loggedIn;

public:
    explicit UserBackend(QObject *parent = nullptr);

    QString getUsername() const;
    QString getPassword() const;
    QString getProviderUrl() const;
    QString getServerUrl() const;
    QString getToken() const;
    bool getLoggedIn() const;

public slots:
    void setUsername(QString username);
    void setPassword(QString password);
    void setProviderUrl(QString providerUrl);
    void setServerUrl(QString serverUrl);
    void setLoggedIn(bool loggedIn);

    void obtainToken();
    void login();

signals:
    void usernameChanged(QString username);
    void passwordChanged(QString password);
    void providerUrlChanged(QString providerUrl);
    void serverUrlChanged(QString serverUrl);
    void tokenChanged(QString token);
    void loggedInChanged(bool loggedIn);
};

#endif // USERBACKEND_H
