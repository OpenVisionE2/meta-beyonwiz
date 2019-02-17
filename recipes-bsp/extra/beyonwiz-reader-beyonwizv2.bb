SUMMARY = "libreader for beyonwiz Model ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "beyonwizv2"

SRCDATE = "20190126"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/beyonwiz/${MACHINE}-libreader-${SRCDATE}.zip"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"

SRC_URI[md5sum] = "d9e2430b9c13ab0745054a4497dd867b"
SRC_URI[sha256sum] = "6d9f44c14ae4f37419f1c8f080feddcebdb30df3b7e2ea89d0085c25c3807c21"
