TEMPLATE = aux

DISTFILES += \
    Doxyfile.in \
    DoxygenLayout.xml

isEmpty(DOXY_BIN_PATH): DOXY_BIN_PATH = /usr/bin/doxygen

exists($$DOXY_BIN_PATH) {
    message("Doxygen found. Documentation building available.")

    DOXYGEN_INPUT_DIR = $${_PRO_FILE_PWD_}/../Intfuorit
    DOXYGEN_OUTPUT_DIR = $$OUT_PWD
    DOXYGEN_LAYOUT_FILE = $${_PRO_FILE_PWD_}/DoxygenLayout.xml
    DOXYGEN_HTML_FOOTER = $${_PRO_FILE_PWD_}/doxyWebFooter.html
    DOXYGEN_QUIET = YES

    doxygen_verbose {
        DOXYGEN_QUIET = NO
        message("Doxygen verbose mode enabled.")
    }

    QT_TAG_FILES += \
            qtcore \
            qtnetwork

    for (qt_tag, QT_TAG_FILES) {
        TF = $$[QT_INSTALL_DOCS]/$${qt_tag}/$${qt_tag}.tags
        exists( $${TF} ) {
            DOXYGEN_QHP_TAGS += $${TF}=qthelp://org.qt-project.$${qt_tag}.$${QT_MAJOR_VERSION}$${QT_MINOR_VERSION}$${QT_PATCH_VERSION}/$${qt_tag}/
            DOXYGEN_HTML_TAGS += $${TF}=$$[QT_INSTALL_DOCS]/$${qt_tag}/
            DOXYGEN_WEB_TAGS += $${TF}=http://doc.qt.io/qt-5/
        }
    }

    doxyfile.input = $${_PRO_FILE_PWD_}/Doxyfile.in
    doxyfile.output = $${OUT_PWD}/Doxyfile
    QMAKE_SUBSTITUTES += doxyfile

    webdocs.commands = sed \'s|@TAGFILES@|$$DOXYGEN_WEB_TAGS|\' $${OUT_PWD}/Doxyfile | \
                       sed \'s|@OUTPUT_DIR@|$$DOXYGEN_OUTPUT_DIR/webdocs|\' | \
                       sed \'s|^HTML_TIMESTAMP .*|HTML_TIMESTAMP = YES|\' | \
                       sed \'s|^SEARCHENGINE .*|SEARCHENGINE = YES|\' | \
                       sed \'s|^DISABLE_INDEX .*|DISABLE_INDEX = NO|\' | \
                       sed \'s|^HTML_DYNAMIC_MENUS .*|HTML_DYNAMIC_MENUS = YES|\' | \
                       sed \'s|^CLASS_DIAGRAMS .*|CLASS_DIAGRAMS = YES|\' | \
                       sed \'s|^ALPHABETICAL_INDEX .*|ALPHABETICAL_INDEX = YES|\' | \
                       sed \'s|^HTML_FOOTER .*|HTML_FOOTER = $$DOXYGEN_HTML_FOOTER|\' > $${OUT_PWD}/Doxyfile.web; \
                       doxygen $${OUT_PWD}/Doxyfile.web

    QMAKE_EXTRA_TARGETS += webdocs

    isEmpty(INSTALL_DOCS_DIR): INSTALL_DOCS_DIR = $$[QT_INSTALL_DOCS]

    install_html_docs {
        message("Generating and installing HTML documentation.")

        htmldocs.files = $$DOXYGEN_OUTPUT_DIR/htmldocs/html/*
        htmldocs.path = $$INSTALL_DOCS_DIR/libintfuorit
        htmldocs.CONFIG += no_check_exist
        htmldocs.commands = sed \'s|@TAGFILES@|$$DOXYGEN_HTML_TAGS|\' $${OUT_PWD}/Doxyfile | \
                            sed \'s|@OUTPUT_DIR@|$$DOXYGEN_OUTPUT_DIR/htmldocs|\' > $${OUT_PWD}/Doxyfile.qhp; \
                            doxygen $${OUT_PWD}/Doxyfile.qhp

        INSTALLS += htmldocs
    }

    isEmpty(QHG_BIN_PATH): QHG_BIN_PATH = $$[QT_HOST_BINS]/qhelpgenerator

    exists($$QHG_BIN_PATH) {
        message("Qhelpgenerator found. QCH documenation building available.")

        install_qhp_docs {
            message("Generating and installing QCH documentation.")

            qhpdocs.files = $$DOXYGEN_OUTPUT_DIR/qtdocs/libintfuorit.qch
            qhpdocs.path = $$INSTALL_DOCS_DIR
            qhpdocs.CONFIG += no_check_exist
            qhpdocs.commands = sed \'s|@TAGFILES@|$$DOXYGEN_QHP_TAGS|\' $${OUT_PWD}/Doxyfile | \
                               sed \'s|@OUTPUT_DIR@|$$DOXYGEN_OUTPUT_DIR/qtdocs|\' | \
                               sed \'s|^GENERATE_QHP .*|GENERATE_QHP = YES|\' > $${OUT_PWD}/Doxyfile.qhp; \
                               doxygen $${OUT_PWD}/Doxyfile.qhp

            INSTALLS += qhpdocs
        }
    }

} else {
    warning("Doxygen not found. Documentation building not available.")
}
