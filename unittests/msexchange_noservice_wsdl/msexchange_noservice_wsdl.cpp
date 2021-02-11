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
#include "KDSoapMessage.h"
#include "KDSoapValue.h"
#include "KDSoapPendingCallWatcher.h"
#include "wsdl_Services_noservice.h"
#include "httpserver_p.h"
#include <QTest>
#include <QEventLoop>
#include <QDebug>

using namespace KDSoapUnitTestHelpers;

class MSExchangeNoServiceTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase()
    {
    }

    void testExchangeMessage()
    {
        HttpServerThread server(queryResponse(), HttpServerThread::Public);
        ExchangeServiceBindingService service(this);
        service.setEndPoint(server.endPoint());

        TNS__ResolveNamesType req;
        req.setReturnFullContactData(true);
        T__NonEmptyArrayOfBaseFolderIdsType folderIds;
        T__FolderIdType folderId;
        folderId.setId(QString::fromLatin1("folderId"));
        QList<T__FolderIdType> folderIdList;
        folderIdList << folderId;
        folderIds.setFolderId(folderIdList);
        req.setParentFolderIds(folderIds);

        T__RequestServerVersion requestServerVersion;
        requestServerVersion.setVersion(T__ExchangeVersionType(T__ExchangeVersionType::Exchange2007_SP1));
        service.setRequestVersionHeader(requestServerVersion);

        T__ExchangeImpersonationType impersonation;
        T__ConnectingSIDType sid;
        sid.setPrincipalName(QString::fromLatin1("dfaure"));
        sid.setPrimarySmtpAddress(QString::fromLatin1("david.faure@kdab.com"));
        sid.setSID(QString::fromLatin1("sid"));
        impersonation.setConnectingSID(sid);
        service.setImpersonationHeader(impersonation);

        service.resolveNames(req);

        // Check what we sent
        QByteArray expectedRequestXml =
            QByteArray(xmlEnvBegin11()) + " xmlns:n1=\"http://schemas.microsoft.com/exchange/services/2006/messages\">"
            "<soap:Header>"
            "<n2:ExchangeImpersonation xmlns:n2=\"http://schemas.microsoft.com/exchange/services/2006/types\"><n2:ConnectingSID>"
            "<n2:PrincipalName>dfaure</n2:PrincipalName>"
            "<n2:SID>sid</n2:SID>"
            "<n2:PrimarySmtpAddress>david.faure@kdab.com</n2:PrimarySmtpAddress>"
            "</n2:ConnectingSID></n2:ExchangeImpersonation>"
            "<n2:RequestServerVersion xmlns:n2=\"http://schemas.microsoft.com/exchange/services/2006/types\" Version=\"Exchange2007_SP1\"/>"
            "</soap:Header>"
            "<soap:Body>"
            "<n1:ResolveNames ReturnFullContactData=\"true\">"
            "<n1:ParentFolderIds><n3:FolderId xmlns:n3=\"http://schemas.microsoft.com/exchange/services/2006/types\" Id=\"folderId\"/></n1:ParentFolderIds>"
            "<n1:UnresolvedEntry/>"
            "</n1:ResolveNames>"
            "</soap:Body>" + xmlEnvEnd()
            + '\n'; // added by QXmlStreamWriter::writeEndDocument
        QVERIFY(xmlBufferCompare(server.receivedData(), expectedRequestXml));
    }

private:
    static QByteArray queryResponse()
    {
        return QByteArray(xmlEnvBegin11()) + " xmlns:sf=\"urn:sobject.partner.soap.sforce.com\"><soap:Body>"
               "<queryResponse>" // TODO
               "</queryResponse>"
               "</soap:Body>" + xmlEnvEnd();
    }
};

QTEST_MAIN(MSExchangeNoServiceTest)

#include "msexchange_noservice_wsdl.moc"
