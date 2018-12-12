TEMPLATE = aux

isEmpty(INSTALL_TRANSLATIONS_DIR): INSTALL_TRANSLATIONS_DIR = $$[QT_INSTALL_TRANSLATIONS]

TRANS_FILES = \
        libintfuorit.ts \
        libintfuorit_de.ts \
        libintfuorit_en_GB.ts \
        libintfuorit_en_US.ts \
        libintfuorit_sv.ts

# TODO: change this to versionAtLeast(QT_VERSION, 5.12.0) supported since Qt 5.9
if (greaterThan(QT_MAJOR_VERSION, 5)|greaterThan(QT_MINOR_VERSION, 11)) {

    CONFIG += lrelease
    QM_FILES_INSTALL_PATH = $$INSTALL_TRANSLATIONS_DIR
    QMAKE_LRELEASE_FLAGS += -idbased

    EXTRA_TRANSLATIONS += $$TRANS_FILES

} else {

    for (t, TRANS_FILES) {
        TRANS_IN += $${_PRO_FILE_PWD_}/$$t
        TRANS_OUT += $${OUT_PWD}/$$t
    }

    qm.files = $$replace(TRANS_OUT, \.ts, .qm)
    qm.path = $$INSTALL_TRANSLATIONS_DIR
    qm.CONFIG += no_check_exist
    qm.commands += cp -af $${TRANS_IN} $${OUT_PWD} && $$[QT_HOST_BINS]/lrelease -idbased $${TRANS_OUT} || :

    INSTALLS += qm
}
