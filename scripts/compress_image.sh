#!/bin/sh
# uso:
# compress_image.sh arquivo_para_comprimir.jpg
TEMPFILE=/tmp/temp.jpg

convert -resize "840x840>" "${1}" pnm:- | /opt/mozjpeg/bin/cjpeg -tune-ms-ssim -quality 70 > ${TEMPFILE}
mv ${TEMPFILE} "${1}"
