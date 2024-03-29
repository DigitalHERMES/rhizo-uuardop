#!/bin/bash
# uso:
# compress_image.sh image_filename.{png,gif,...} [output.{jpg,avif,heic,vvc}]

## env vars:
# VVC_ENC: vvc enc binary
# TARGET SIZE: target size

# initial VVC QP... it will only get bigger...
VVC_QP=39

QUALITY=75 # initial start quality to try for jpeg

VVC_ENC=${VVC_ENC:=/root/vvenc/install/bin/vvencapp}
EVC_ENC=${EVC_ENC:=/root/xeve/build/bin/xeve_app}
AV1_ENC=${AV1_ENC:=/root/aom/build2/aomenc}

# reduce...
TARGET_SIZE=${TARGET_SIZE:=80000} # 10kB == 80000 bits

# logic for qp-based bitrate control
MAX_SIZE=$((${TARGET_SIZE} / 8)) # 10kB file size limit

#echo ${VVC_ENC}

# vvc and evc  are the state of the art, no integration to userlad
# avif and heic are already implemented and integrated to userland
# jpg is the legacy format
# IMAGE_FORMAT=${IMAGE_FORMAT:=heic}

if [ $# -lt 2 ]; then
  echo "Usage: $0 image_filename.{png,gif,...} [output.{jpg,avif,heic,vvc}]"
  exit 1
fi

input_file=${input_file:=${1}}
output_file=${output_file:=${2}}

IMAGE_FORMAT="${output_file##*.}"

TEMPFILE=/tmp/temp-$$.${IMAGE_FORMAT}
TEMPFILEYUV=/tmp/temp-$$.yuv

echo "Original file size = $(stat -c%s "${input_file}")"

# while [[ stat -c ${input_file} ]]
# echo $(stat -c%s "${input_file}")
cp -f "${input_file}" ${TEMPFILE}

if [ ${IMAGE_FORMAT} = "evc" ]; then
    resolution=$(convert-im6 -debug all -resize "840x840>" "${input_file}" -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV} 2>&1 | grep -i "Heap " | cut -d " " -f 7 | sed -n 5p)
    width=$(echo -n ${resolution} | cut -f 1 -d x)
    height=$(echo -n ${resolution} | cut -f 2 -d x)

    # my ugly workaround to round up the dimensions
    width=$(( (${width} / 8) * 8 ))
    height=$(( (${height} / 8) * 8 ))
    resolution=${width}x${height}

    rm -f ${TEMPFILEYUV}

    convert-im6 -resize "${resolution}!" "${input_file}" -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV}


    echo ${EVC_ENC} -w ${width} -h ${height} -z 1 -m 2 --profile main --preset medium --bitrate $(( ${TARGET_SIZE} / 1000 ))  -i ${TEMPFILEYUV} -o  ${TEMPFILE}
    ${EVC_ENC} -w ${width} -h ${height} -z 1 -m 2 --profile main --preset medium --bitrate $(( ${TARGET_SIZE} / 1000 ))  -i ${TEMPFILEYUV} -o  ${TEMPFILE}

    rm -f ${TEMPFILEYUV}

elif [ ${IMAGE_FORMAT} = "vvc" ]; then

    #    ffmpeg -i ${input_file} -c:v rawvideo -pixel_format yuv420p -vf scale=-1:840  output_720x480p.yuv
    resolution=$(convert-im6 -debug all -resize "840x840>" "${input_file}" -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV} 2>&1 | grep -i "Heap " | cut -d " " -f 7 | sed -n 5p)
    width=$(echo -n ${resolution} | cut -f 1 -d x)
    height=$(echo -n ${resolution} | cut -f 2 -d x)

    # my ugly workaround to round up the dimensions
    width=$(( (${width} / 4) * 4 ))
    height=$(( (${height} / 4) * 4 ))
    resolution=${width}x${height}

    rm -f ${TEMPFILEYUV}

    convert-im6 -resize "${resolution}!" "${input_file}" -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV}

    ## bitrate control using rc
    #   ${VVC_ENC} -i ${TEMPFILEYUV} --profile main_10_still_picture --qpa 1 -t 2 -r 1 -b ${TARGET_SIZE} -s ${resolution} --preset medium -c yuv420 -o  ${TEMPFILE}

    ${VVC_ENC} -i ${TEMPFILEYUV} --profile main_10_still_picture --qpa 1 -t 2 -r 1 --qp ${VVC_QP} -s ${resolution} --preset medium -c yuv420 -o  ${TEMPFILE}

    while [ "$(stat -c%s "${TEMPFILE}")" -gt "$MAX_SIZE" ] && [ "$VVC_QP" -lt "61" ]; do
      VVC_QP=$((VVC_QP+3))
      ${VVC_ENC} -i ${TEMPFILEYUV} --profile main_10_still_picture --qpa 1 -t 2 -r 1 --qp ${VVC_QP} -s ${resolution} --preset medium -c yuv420 -o  ${TEMPFILE}

    done;

    rm -f ${TEMPFILEYUV}

elif [ ${IMAGE_FORMAT} = "avif" ]; then

# TODO
  ${AV1_ENC} --target-bitrate=${TARGET_SIZE} --end-usage=cbr --bit-depth=8 ...

elif [ ${IMAGE_FORMAT} = "jpg" ]; then

  while [ "$(stat -c%s "${TEMPFILE}")" -gt "$MAX_SIZE" ] && [ "${QUALITY}" -gt "5" ]; do
    convert -resize "840x840>" "${input_file}" pnm:- | /opt/mozjpeg/bin/cjpeg -quality ${QUALITY} > ${TEMPFILE}
    QUALITY=$((QUALITY-10))
  done;

elif [ ${IMAGE_FORMAT} = "heic" ]; then

# TODO
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


# with output file specified
if [ $# -eq 2 ]; then
  mv ${TEMPFILE} "${output_file}"
fi
