/****************************************************************************
**
** This file is part of the KD Soap library.
**
** SPDX-FileCopyrightText: 2010-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: LicenseRef-KDAB-KDSoap-AGPL3-Modified OR LicenseRef-KDAB-KDSoap OR LicenseRef-KDAB-KDSoap-US
**
** Licensees holding valid commercial KD Soap licenses may use this file in
** accordance with the KD Soap Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not clear to you.
**
****************************************************************************/
#ifndef KDSOAPSERVERTHREAD_P_H
#define KDSOAPSERVERTHREAD_P_H

#include <QThread>
#include <QSemaphore>
#include <QMutex>
#include <QHash>
class KDSoapServer;
class KDSoapSocketList;

class KDSoapServerThreadImpl : public QObject
{
    Q_OBJECT
public:
    KDSoapServerThreadImpl();
    ~KDSoapServerThreadImpl();

public Q_SLOTS:
    void handleIncomingConnection(int socketDescriptor, KDSoapServer *server);
    void disconnectSocketsForServer(KDSoapServer *server, QSemaphore *semaphore);
    void quit();

public:
    int socketCount();
    int socketCountForServer(const KDSoapServer *server);
    int totalConnectionCountForServer(const KDSoapServer *server);
    void resetTotalConnectionCountForServer(const KDSoapServer *server);

    void addIncomingConnection();
private:
    QMutex m_socketListMutex;
    KDSoapSocketList *socketListForServer(KDSoapServer *server);
    typedef QHash<KDSoapServer *, KDSoapSocketList *> SocketLists;
    SocketLists m_socketLists;

    QAtomicInt m_incomingConnectionCount;
};

class KDSoapServerThread : public QThread
{
    Q_OBJECT
public:
    explicit KDSoapServerThread(QObject *parent = 0);
    ~KDSoapServerThread();

    void startThread();
    void quitThread();

    int socketCount() const;
    int socketCountForServer(const KDSoapServer *server) const;
    int totalConnectionCountForServer(const KDSoapServer *server) const;
    void resetTotalConnectionCountForServer(const KDSoapServer *server);

    void disconnectSocketsForServer(KDSoapServer *server, QSemaphore &semaphore);
    void handleIncomingConnection(int socketDescriptor, KDSoapServer *server);

protected:
    virtual void run() override;

private:
    void start(); // use startThread instead
    void quit(); // use quitThread instead
    KDSoapServerThreadImpl *d;
    QSemaphore m_semaphore;
};

#endif // KDSOAPSERVERTHREAD_P_H
