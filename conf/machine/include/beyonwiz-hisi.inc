# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

KERNELVERSION = "4.4.35"

BOX_BRAND = "beyonwiz"

DISTRO_FEATURES_remove += "x11 wayland"

EXTRA_OECONF_append_pn-enigma2 = "--with-lcddev=/dev/null --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250  --with-fillaccelerationthreshold=190000"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"
CHIPSET = "Hi3798Mv200"

MTD_KERNEL = "mmcblk0p12"
MTD_ROOTFS = "mmcblk0p16"

KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	beyonwiz-dvb-modules-${MACHINE} \
	beyonwiz-loadmodules-${MACHINE} \
	beyonwiz-opengl-${MACHINE} \ 
	beyonwiz-libs-${MACHINE} \
	beyonwiz-hihalt-${MACHINE} \
	beyonwiz-reader-${MACHINE} \
	beyonwiz-libreader-${MACHINE} \
	beyonwiz-partitions-${MACHINE} \
	beyonwiz-buildimage \
	e2fsprogs-resize2fs \
	gptfdisk \
	"

MACHINE_FEATURES += "switchoff 7segment hdmicec textlcd emmc mmc dvb-c alsa hisil multitranscoding HDMI AV_JACK vfdsymbol kodi19"

IMAGE_CLASSES  += "beyonwiz-emmc_image"
IMAGE_FSTYPES += "beyonwizemmc"
IMAGE_ROOTFS_SIZE ?= "524288"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

#Provider
PREFERRED_VERSION_linux-beyonwiz = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/kernel = "linux-beyonwiz"
PREFERRED_PROVIDER_virtual/egl ?= "beyonwiz-opengl-${MACHINE}" 
PREFERRED_PROVIDER_virtual/libgles1 ?= "beyonwiz-opengl-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "beyonwiz-opengl-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "beyonwiz-blindscan-${MACHINE}"
PREFERRED_RPROVIDER_showiframe = "beyonwiz-showiframe-${MACHINE}"
PREFERRED_RPROVIDER_aio-grab = "beyonwiz-grab-${MACHINE}"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa15.inc


require conf/machine/include/soc-family.inc

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-spark --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

IMAGE_CMD_beyonwizemmc_append = " \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	mv -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ext4 ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/rootfs.ext4; \
	cd ${IMAGE_ROOTFS}; \
	tar -cvf ${DEPLOY_DIR_IMAGE}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
	mv -f ${DEPLOY_DIR_IMAGE}/rootfs.tar ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/rootfs.tar; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/${KERNEL_FILE}; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt; \
	cd ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions; \
	mkupdate -s 00000003-00000001-01010101 -f ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/emmc_partitions.xml -d ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	cd ${DEPLOY_DIR_IMAGE}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.manifest ${IMAGE_NAME}_usb.zip.manifest; \
	zip -j ${IMAGE_NAME}_recovery_emmc.zip ${DEPLOY_DIR_IMAGE}/usb_update.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/donate.txt ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/bootargs.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/fastboot.bin ${DEPLOY_DIR_IMAGE}/${MACHINE}-partitions/apploader.bin; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
	rm -f ${DEPLOY_DIR_IMAGE}/usb_update.bin; \
	rm -Rf ${IMAGEDIR}; \
	rm -Rf userdata; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/userdata; \
	"

EXTRA_ALSA = "mv200"

RCNAME = "beyonwiz2"
