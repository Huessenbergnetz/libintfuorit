TARGET = intfuorit
TEMPLATE = lib

VER_MAJ = 1
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

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

isEmpty(PREFIX): PREFIX = $$[QT_INSTALL_PREFIX]
isEmpty(INSTALL_LIB_DIR): INSTALL_LIB_DIR = $$[QT_INSTALL_LIBS]
isEmpty(INSTALL_TRANSLATIONS_DIR): INSTALL_TRANSLATIONS_DIR = $$[QT_INSTALL_TRANSLATIONS]

PUBLIC_HEADERS = \
    Intfuorit \
    intfuorit.h \
    Error \
    error.h \
    intfuorit_global.h \
    networkaccessmanagerfactory.h \
    NetworkAccessManagerFactory \
    API/component.h \
    API/getallbreaches.h \
    API/GetAllBreaches \
    API/getbreachesforaccount.h \
    API/GetBreachesForAccount \
    API/getpastesforaccount.h \
    API/GetPastesForAccount \
    API/getbreachedsite.h \
    API/GetBreachedSite \
    API/checkpwnedpassword.h \
    API/CheckPwnedPassword \
    API/getalldataclasses.h \
    API/GetAllDataClasses \
    Objects/breach.h \
    Objects/Breach \
    Objects/paste.h \
    Objects/Paste \
    Models/basemodel.h \
    Models/breachesmodel.h \
    Models/breacheslistmodel.h \
    Models/BreachesListModel \
    Models/basefiltermodel.h \
    Models/breacheslistfiltermodel.h \
    Models/BreachesListFilterModel \
    Models/pastesmodel.h \
    Models/pasteslistmodel.h \
    Models/PastesListModel

PRIVATE_HEADERS = \
    error_p.h \
    API/component_p.h \
    API/getallbreaches_p.h \
    API/getpastesforaccount_p.h \
    API/getbreachesforaccount_p.h \
    API/getbreachedsite_p.h \
    API/checkpwnedpassword_p.h \
    API/getalldataclasses_p.h \
    Objects/breach_p.h \
    Objects/paste_p.h \
    Models/basemodel_p.h \
    Models/breachesmodel_p.h \
    Models/breacheslistmodel_p.h \
    Models/basefiltermodel_p.h \
    Models/breacheslistfiltermodel_p.h \
    Models/pastesmodel_p.h \
    Models/pasteslistmodel_p.h

HEADERS += $$PRIVATE_HEADERS $$PUBLIC_HEADERS

SOURCES +=  \
    intfuorit.cpp \
    error.cpp \
    API/component.cpp \
    API/getallbreaches.cpp \
    API/getbreachesforaccount.cpp \
    API/getpastesforaccount.cpp \
    API/getbreachedsite.cpp \
    API/checkpwnedpassword.cpp \
    API/getalldataclasses.cpp \
    Objects/paste.cpp \
    Objects/breach.cpp \
    Models/basemodel.cpp \
    Models/breachesmodel.cpp \
    Models/breacheslistmodel.cpp \
    Models/basefiltermodel.cpp \
    Models/breacheslistfiltermodel.cpp \
    Models/pastesmodel.cpp \
    Models/pasteslistmodel.cpp \
    networkaccessmanagerfactory.cpp

!contains(CONFIG, no_install_dev_files) {
    isEmpty(INSTALL_HEADERS_DIR): INSTALL_HEADERS_DIR = $$[QT_INSTALL_HEADERS]

    basePath = $${dirname(PWD)}
    for(header, PUBLIC_HEADERS) {
        relPath = $${relative_path($$header, $$basePath)}
        path = $${INSTALL_HEADERS_DIR}/Intfuorit/$${dirname(relPath)}
        eval(headers_$${path}.files += $$relPath)
        eval(headers_$${path}.path = $$path)
        eval(INSTALLS *= headers_$${path})
    }

    pkgconfigfile.input = intfuorit.pc.in
    pkgconfigfile.output = $${OUT_PWD}/intfuorit.pc
    pkgconfigfile.path = $$[QT_INSTALL_LIBS]/pkgconfig
    pkgconfigfile.files = $$pkgconfigfile.output

    QMAKE_SUBSTITUTES += pkgconfigfile

    INSTALLS += pkgconfigfile
}

clazy {
    DEFINES += CLAZY
    QMAKE_CXX = clang
    QMAKE_CXXFLAGS += "-Xclang -load -Xclang ClangLazy.so -Xclang -add-plugin -Xclang clang-lazy -Xclang -plugin-arg-clazy -Xclang level0,level1,level2"
}

target = $$TARGET
target.path = $$INSTALL_LIB_DIR
INSTALLS += target

DISTFILES += \
    intfuorit.pc.in
