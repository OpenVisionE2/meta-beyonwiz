SUMMARY = "libreader for ${MACHINE}"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "CLOSED"
PACKAGE_ARCH = "${MACHINE_ARCH}"

RDEPENDS_${PN} = "libsdl"

COMPATIBLE_MACHINE = "^(beyonwizv2)$"

SRCDATE = "20200415"

PV = "${SRCDATE}"

SRC_URI = "http://source.mynonpublic.com/beyonwiz/${MACHINE}-libreader-${SRCDATE}.tar.gz"

SRC_URI[md5sum] = "b517c915036eadf631ecb58cff6795ca"
SRC_URI[sha256sum] = "7a7cb4d74a6510056fec5623ffe2ebfc4a608805392bf0f2ee777dce6c1a846b"

S = "${WORKDIR}"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/libreader ${D}/${bindir}
}

do_package_qa() {
}

FILES_${PN}  = "${bindir}/libreader"
