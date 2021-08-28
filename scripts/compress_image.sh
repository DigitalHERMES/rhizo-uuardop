#!/bin/bash
# uso:
# compress_image.sh arquivo_para_comprimir.jpg
MAX_SIZE=${MAX_SIZE:=51200} # 50kB file size limit
QUALITY=75 # initial start quality to try for jpeg

VVC_ENC=${VVC_ENC:=/root/vvenc/install/bin/vvencapp}
# reduce...
TARGET_SIZE=${TARGET_SIZE:=80000} # 10kB == 80000 bits

echo ${VVC_ENC}

# vvc and evc  are the state of the art, no integration to userlad
# avif and heic are already implemented and integrated to userland
# jpg is the legacy format
# IMAGE_FORMAT=${IMAGE_FORMAT:=heic} 

if [ $# -lt 2 ]; then
#  echo "Usage: $0 image_filename.jpg"
  echo "Usage: $0 image_filename.{png,gif,...} output.{jpg,avif,heic,vvc}"
  exit 1
fi

input_file=${1}
output_file=${2}

IMAGE_FORMAT="${output_file##*.}"



TEMPFILE=/tmp/temp-$$.${IMAGE_FORMAT}
TEMPFILEYUV=/tmp/temp-$$.yuv

echo "Original file size = $(stat -c%s "${input_file}")"

# while [[ stat -c ${input_file} ]]
# echo $(stat -c%s "${input_file}")
cp -f "${input_file}" ${TEMPFILE}

if [ ${IMAGE_FORMAT} = "evc" ]; then

    echo NOT IMPLEMENTED
  
elif [ ${IMAGE_FORMAT} = "vvc" ]; then

    resolution=$(convert-im6 -debug all -resize "840x840>" ${input_file} -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV} 2>&1 | grep -i Heap|  sed -n 2p |  rev | cut -f2 -d " " | rev)
    echo $resolution
    #    ${VVC_ENC} -i ${TEMPFILEYUV} --qpa 1 -t 2 -r 1 -b 80000 -s $resolution --preset slow -c yuv420 -o  ${TEMPFILE}
# use the expert app and 8-bit 
   ${VVC_ENC} -i ${TEMPFILEYUV} --qpa 1 -t 2 -r 1 -b ${TARGET_SIZE} -s ${resolution} --preset medium -c yuv420 -o  ${TEMPFILE}
    rm -f ${TEMPFILEYUV}
    #
    #    ffmpeg -i DRONE_DJI_0008.JPG -c:v rawvideo -pixel_format yuv420p -vf scale=-1:840  output_720x480p.yuv
    

elif [ ${IMAGE_FORMAT} = "avif" ]; then

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
