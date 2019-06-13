TEMPLATE = lib
CONFIG += qt plugin
QT += qml

TARGET = qmlintfuoritplugin

LIBS += -L$$OUT_PWD/../../../../Intfuorit -lintfuorit
INCLUDEPATH += $$PWD/../../../../

SOURCES += \
    qmlintfuoritplugin.cpp

DISTFILES += qmldir

isEmpty(QT_INSTALL_QML_PATH): QT_INSTALL_QML_PATH = $$[QT_INSTALL_QML]
isEmpty(QML_PLUGIN_INSTALL_DIR): QML_PLUGIN_INSTALL_DIR = $${QT_INSTALL_QML_PATH}/de/huessenbergnetz/intfuorit

target = $$TARGET
target.path = $$QML_PLUGIN_INSTALL_DIR
INSTALLS += target

qmlDir.path = $$QML_PLUGIN_INSTALL_DIR
qmlDir.files = qmldir
INSTALLS += qmlDir

!contains(CONFIG, no_install_dev_files) {
    qmlTypes.path = $$QML_PLUGIN_INSTALL_DIR
    qmlTypes.files = plugins.qmltypes
    INSTALLS += qmlTypes
}

clazy {
    DEFINES += CLAZY
    QMAKE_CXX = clazy
    QMAKE_CXXFLAGS += "-Xclang -plugin-arg-clazy -Xclang level0,level1,level2"
}
