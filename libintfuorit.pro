TARGET = intfuorit
TEMPLATE = lib

VER_MAJ = 0
VER_MIN = 0
VER_PAT = 0

VERSION = $${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

QT += network
QT -= gui

CONFIG -= console
CONFIG -= app_bundle
CONFIG += shared
CONFIG += c++11
CONFIG += no_keywords

DEFINES += INTFUORIT_LIBRARY

DEFINES += LIBINTFUORIT_VERSION_STRING=\"\\\"$${VERSION}\\\"\"

isEmpty(PREFIX): PREFIX = $$[QT_INSTALL_PREFIX]
isEmpty(INSTALL_LIB_DIR): INSTALL_LIB_DIR = $$[QT_INSTALL_LIBS]
isEmpty(INSTALL_TRANSLATIONS_DIR): INSTALL_TRANSLATIONS_DIR = $$[QT_INSTALL_TRANSLATIONS]

!contains(CONFIG, no_install_dev_files) {
    isEmpty(INSTALL_HEADERS_DIR): INSTALL_HEADERS_DIR = $$[QT_INSTALL_HEADERS]

    INSTALL_HEADERS += \
        Intfuorit/Error \
        Intfuorit/error.h \
        Intfuorit/intfuorit_global.h

    basePath = $${dirname(PWD)}
    for(header, INSTALL_HEADERS) {
        relPath = $${relative_path($$header, $$basePath)}
        path = $${INSTALL_HEADERS_DIR}/$${dirname(relPath)}
        eval(headers_$${path}.files += $$relPath)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }

    pkgconfigfile.input = intfuorit.pc.in
    pkgconfigfile.output = intfuorit.pc
    pkgconfigfile.path = $$[QT_INSTALL_LIBS]/pkgconfig
    pkgconfigfile.files = $$pkgconfigfile.output

    QMAKE_SUBSTITUTES += pkgconfigfile

    INSTALLS += pkgconfigfile
}

target = $$TARGET
target.path = $$INSTALL_LIB_DIR
INSTALLS += target

langfiles.path = $$INSTALL_TRANSLATIONS_DIR
langfiles.files = translations/*.qm
INSTALLS += langfiles

DISTFILES += \
    intfuorit.pc.in

HEADERS += \
    Intfuorit/intfuorit_global.h \
    Intfuorit/error.h \
    Intfuorit/error_p.h

SOURCES += \
    Intfuorit/error.cpp
