SUMMARY = "player daemon helper"
MAINTAINER = "beyonwiz"

require conf/license/license-gplv2.inc

COMPATIBLE_MACHINE = "^(beyonwizv2)$"

SRC_URI = "file://beyonwiz-libreader-beyonwizv2.sh"

INITSCRIPT_NAME = "beyonwiz-libreader"
INITSCRIPT_PARAMS = "start 05 S ."

inherit update-rc.d

S = "${WORKDIR}"

do_compile() {
}

do_install() {
    install -d ${D}${INIT_D_DIR}/
    install -m 0755 ${WORKDIR}/beyonwiz-libreader-beyonwizv2.sh ${D}${INIT_D_DIR}/beyonwiz-libreader
}
