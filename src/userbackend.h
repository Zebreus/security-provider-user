#ifndef USERBACKEND_H
#define USERBACKEND_H

#include <QObject>

class UserBackend : public QObject
{
    Q_OBJECT
public:
    explicit UserBackend(QObject *parent = nullptr);

signals:

};

#endif // USERBACKEND_H
