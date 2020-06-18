#!/bin/bash
# uso:
# compress_image.sh arquivo_para_comprimir.jpg
MAX_SIZE=${MAX_SIZE:=51200} # 50kB file size limit
QUALITY=75 # initial start quality to try...

TEMPFILE=/tmp/temp-$$.jpg


if [ $# -lt 1 ]; then
  echo "Usage: $0 image_filename.jpg"
  echo "Usage: $0 image_filename.{png,gif,...} output.jpg"
  exit 1
fi

# while [[ stat -c ${1} ]]
# echo $(stat -c%s "${1}")
cp -f "${1}" ${TEMPFILE}

while [ "$(stat -c%s "${TEMPFILE}")" -gt "$MAX_SIZE" ] && [ "$QUALITY" -gt "5" ]; do
#  echo $(stat -c%s "${TEMPFILE}")
  convert -resize "840x840>" "${1}" pnm:- | /opt/mozjpeg/bin/cjpeg -quality ${QUALITY} > ${TEMPFILE}
  QUALITY=$((QUALITY-10))
#  echo ${QUALITY}
done;

if [ $# -eq 1 ]; then
  mv ${TEMPFILE} "${1}"
fi

if [ $# -eq 2 ]; then
  mv ${TEMPFILE} "${2}"
fi
