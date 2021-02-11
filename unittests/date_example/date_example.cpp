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

#include "KDSoapClientInterface.h"
#include "wsdl_date_example.h"
#include <QTest>
#include <QEventLoop>
#include <QDebug>

class DateExampleWSDL : public QObject
{
    Q_OBJECT
public:

private slots:
    void slotCheckCompilation()
    {
        DateExample service;
        StringToDateJob job(&service);
        QDate result = job.dateObject();
        QCOMPARE(result, QDate());
    }

};

QTEST_MAIN(DateExampleWSDL)

#include "date_example.moc"

