## This file is part of the KD Soap library.
##
## SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
##
## SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDSoap OR LicenseRef-KDAB-KDSoap-US
##
## Licensees holding valid commercial KD Soap licenses may use this file in
## accordance with the KD Soap Commercial License Agreement provided with
## the Software.
##
## Contact info@kdab.com if any conditions of this licensing are not clear to you.
##

include( $${TOP_SOURCE_DIR}/examples/examples.pri )

HEADERS = mainwindow.h
SOURCES = bank_gui.cpp mainwindow.cpp
RESOURCES = resources.qrc
KDWSDL = BLZService.wsdl

# This is our only GUI program :)
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
} else {
    QT += gui
}
CONFIG -= console
macx: CONFIG += app_bundle