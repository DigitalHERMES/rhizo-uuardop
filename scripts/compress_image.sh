#!/bin/bash
# uso:
# compress_image.sh arquivo_para_comprimir.jpg
MAX_SIZE=${MAX_SIZE:=51200} # 50kB file size limit
QUALITY=75 # initial start quality to try...

# IMAGE_FORMAT=${IMAGE_FORMAT:=heic} # avif, heic, jpg or vvc

if [ $# -lt 2 ]; then
#  echo "Usage: $0 image_filename.jpg"
  echo "Usage: $0 image_filename.{png,gif,...} output.{jpg,avif,heic,vvc}"
  exit 1
fi

input_file=${1}
output_file=${2}

IMAGE_FORMAT="${output_file##*.}"



TEMPFILE=/tmp/temp-$$.${IMAGE_FORMAT}

echo "Original file size = $(stat -c%s "${input_file}")"

# while [[ stat -c ${input_file} ]]
# echo $(stat -c%s "${input_file}")
cp -f "${input_file}" ${TEMPFILE}


if [ ${IMAGE_FORMAT} = "avif" ]; then

  while [ "$(stat -c%s "${TEMPFILE}")" -gt "$MAX_SIZE" ] && [ "$QUALITY" -gt "5" ]; do
    convert -resize "840x840>"  "${input_file}" -quality ${QUALITY} ${TEMPFILE}
    QUALITY=$((QUALITY-10))
  done;

elif [ ${IMAGE_FORMAT} = "jpg" ]; then

  while [ "$(stat -c%s "${TEMPFILE}")" -gt "$MAX_SIZE" ] && [ "$QUALITY" -gt "5" ]; do
    convert -resize "840x840>" "${input_file}" pnm:- | /opt/mozjpeg/bin/cjpeg -quality ${QUALITY} > ${TEMPFILE}
    QUALITY=$((QUALITY-10))
  done;

elif [ ${IMAGE_FORMAT} = "heic" ]; then

  while [ "$(stat -c%s "${TEMPFILE}")" -gt "$MAX_SIZE" ] && [ "$QUALITY" -gt "5" ]; do
    convert -resize "840x840>"  "${input_file}" -quality ${QUALITY} ${TEMPFILE}
    QUALITY=$((QUALITY-10))
  done;

else
  echo "Unsupported extension: ${output_file##*.}"
  exit
fi

# in place
#if [ $# -eq 1 ]; then
#  mv ${TEMPFILE} "${input_file}"
#fi

echo "Final file size: $(stat -c%s "${TEMPFILE}")"
echo "Quality level: ${QUALITY}"


# with output file specified
if [ $# -eq 2 ]; then
  mv ${TEMPFILE} "${output_file}"
fi
