/****************************************************************************
**
** This file is part of the KD Soap library.
**
** SPDX-FileCopyrightText: 2010-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDSoap OR LicenseRef-KDAB-KDSoap-US
**
** Licensees holding valid commercial KD Soap licenses may use this file in
** accordance with the KD Soap Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not clear to you.
**
****************************************************************************/
#include "KDSoapPendingCallWatcher.h"
#include "KDSoapPendingCallWatcher_p.h"
#include "KDSoapPendingCall_p.h"
#include <QNetworkReply>
#include <QDebug>

KDSoapPendingCallWatcher::KDSoapPendingCallWatcher(const KDSoapPendingCall &call, QObject *parent)
    : QObject(parent), KDSoapPendingCall(call),
      d(new Private(this))
{
    connect(call.d->reply.data(), SIGNAL(finished()), this, SLOT(_kd_slotReplyFinished()));
}

KDSoapPendingCallWatcher::~KDSoapPendingCallWatcher()
{
    delete d;
}

#if 0
void KDSoapPendingCallWatcher::waitForFinished()
{
    // TODO?
}
#endif

void KDSoapPendingCallWatcher::Private::_kd_slotReplyFinished()
{
    // Workaround Qt-4.5 emitting finished twice in testCallRefusedAuth
    disconnect(q->KDSoapPendingCall::d->reply.data(), SIGNAL(finished()), q, nullptr);
    emit q->finished(q);
}

#include "moc_KDSoapPendingCallWatcher.cpp"
