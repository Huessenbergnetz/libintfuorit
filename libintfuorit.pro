TARGET = intfuorit
TEMPLATE = lib

VER_MAJ = 0
VER_MIN = 0
VER_PAT = 1

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

!contains(CONFIG, no_install_dev_files) {
    isEmpty(INSTALL_HEADERS_DIR): INSTALL_HEADERS_DIR = $$[QT_INSTALL_HEADERS]

    INSTALL_HEADERS += \
        Intfuorit/Error \
        Intfuorit/error.h \
        Intfuorit/intfuorit_global.h \
        Intfuorit/API/component.h \
        Intfuorit/API/getallbreaches.h \
        Intfuorit/API/GetAllBreaches \
        Intfuorit/Objects/breach.h \
        Intfuorit/Objects/Breach \
        Intfuorit/Models/basemodel.h \
        Intfuorit/Models/breachesmodel.h \
        Intfuorit/Models/breacheslistmodel.h \
        Intfuorit/Models/BreachesListModel \
        Intfuorit/Models/basefiltermodel.h \
        Intfuorit/Models/breacheslistfiltermodel.h \
        Intfuorit/Models/BreachesListFilterModel

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

contains(CONFIG, clazy) {
    DEFINES+=CLAZY
    QMAKE_CXXFLAGS += "-Xclang -load -Xclang ClangLazy.so -Xclang -add-plugin -Xclang clang-lazy"
}


isEmpty(QHG_BIN_PATH): QHG_BIN_PATH = $$[QT_INSTALL_BINS]/qhelpgenerator
isEmpty(QT_TAG_FILES_PATH): QT_TAG_FILES_PATH = $$[QT_INSTALL_DOCS]
DOXYGEN_INPUT_DIR = $$PWD
DOXYGEN_OUTPUT_DIR = $$PWD
QT_TAG_FILES += \
        qtcore\
        qtnetwork

for (qt_tag, QT_TAG_FILES) {
    exists( $$[QT_INSTALL_DOCS]/$${qt_tag}/$${qt_tag}.tags ) {
        DOXYGEN_QHP_TAGS += $$[QT_INSTALL_DOCS]/$${qt_tag}/$${qt_tag}.tags=qthelp://org.qt-project.$${qt_tag}.$${QT_MAJOR_VERSION}$${QT_MINOR_VERSION}$${QT_PATCH_VERSION}/$${qt_tag}/
        DOXYGEN_HTML_TAGS += $$[QT_INSTALL_DOCS]/$${qt_tag}/$${qt_tag}.tags=$$[QT_INSTALL_DOCS]/$${qt_tag}/
        DOXYGEN_WEB_TAGS += $$[QT_INSTALL_DOCS]/$${qt_tag}/$${qt_tag}.tags=http://doc.qt.io/qt-5/
    }
}


doxyfile.input = Doxyfile.in
doxyfile.output = $$PWD/Doxyfile
QMAKE_SUBSTITUTES += doxyfile

qhpdocs.commands = sed \'s|@TAGFILES@|$$DOXYGEN_QHP_TAGS|\' $$PWD/Doxyfile | sed \'s|@OUTPUT_DIR@|$$DOXYGEN_OUTPUT_DIR/qtdocs|\' | sed \'s|^GENERATE_QHP .*|GENERATE_QHP = YES|\' > $$PWD/Doxyfile.qhp; doxygen $$PWD/Doxyfile.qhp

htmldocs.commands = sed \'s|@TAGFILES@|$$DOXYGEN_HTML_TAGS|\' $$PWD/Doxyfile | sed \'s|@OUTPUT_DIR@|$$DOXYGEN_OUTPUT_DIR/htmldocs|\' > $$PWD/Doxyfile.html; doxygen $$PWD/Doxyfile.html

webdocs.commands = sed \'s|@TAGFILES@|$$DOXYGEN_WEB_TAGS|\' $$PWD/Doxyfile | sed \'s|@OUTPUT_DIR@|$$DOXYGEN_OUTPUT_DIR/webdocs|\' | sed \'s|^HTML_TIMESTAMP .*|HTML_TIMESTAMP = YES|\' > $$PWD/Doxyfile.web; doxygen $$PWD/Doxyfile.web

docs.commands = @echo Documentation built
docs.depends = qhpdocs htmldocs webdocs

QMAKE_EXTRA_TARGETS += docs qhpdocs htmldocs webdocs

contains(CONFIG, install_doc_files) {
    isEmpty(INSTALL_DOCS_DIR): INSTALL_DOCS_DIR = $$[QT_INSTALL_DOCS]
}

target = $$TARGET
target.path = $$INSTALL_LIB_DIR
INSTALLS += target

langfiles.path = $$INSTALL_TRANSLATIONS_DIR
langfiles.files = translations/*.qm
INSTALLS += langfiles

DISTFILES += \
    intfuorit.pc.in \
    Doxyfile.in

HEADERS += \
    Intfuorit/intfuorit_global.h \
    Intfuorit/error.h \
    Intfuorit/error_p.h \
    Intfuorit/API/component.h \
    Intfuorit/API/component_p.h \
    Intfuorit/API/getallbreaches.h \
    Intfuorit/API/getallbreaches_p.h \
    Intfuorit/Objects/breach.h \
    Intfuorit/Objects/breach_p.h \
    Intfuorit/Models/basemodel.h \
    Intfuorit/Models/basemodel_p.h \
    Intfuorit/Models/breachesmodel.h \
    Intfuorit/Models/breachesmodel_p.h \
    Intfuorit/Models/breacheslistmodel.h \
    Intfuorit/Models/breacheslistmodel_p.h \
    Intfuorit/Models/basefiltermodel.h \
    Intfuorit/Models/basefiltermodel_p.h \
    Intfuorit/Models/breacheslistfiltermodel.h \
    Intfuorit/Models/breacheslistfiltermodel_p.h

SOURCES += \
    Intfuorit/error.cpp \
    Intfuorit/API/component.cpp \
    Intfuorit/API/getallbreaches.cpp \
    Intfuorit/Objects/breach.cpp \
    Intfuorit/Models/basemodel.cpp \
    Intfuorit/Models/breachesmodel.cpp \
    Intfuorit/Models/breacheslistmodel.cpp \
    Intfuorit/Models/basefiltermodel.cpp \
    Intfuorit/Models/breacheslistfiltermodel.cpp
