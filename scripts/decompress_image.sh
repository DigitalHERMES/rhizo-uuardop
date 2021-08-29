#!/bin/bash
# usage:
# decompress_image.sh file.vvc file.jpg

if [ $# -lt 2 ]; then
  echo "Usage: $0 image_filename.{vvc,evc,avif,heic} output.jpg"
  exit 1
fi

VVC_DEC=${VVC_DEC:=/root/vvdec/install/bin/vvdecapp}
EVC_DEC=${EVC_DEC:=/root/xevd/build/bin/xevd_app}
CJPEG_ENC=${CJPEG:=/opt/mozjpeg/bin/cjpeg}

input_file=${1}
output_file=${2}

IMAGE_FORMAT="${input_file##*.}"

TEMPFILEYUV=/tmp/temp-$$.yuv
TEMPFILEYUV2=/tmp/temp-$$-2.yuv

if [ ${IMAGE_FORMAT} = "vvc" ]; then


    resolution=$(${VVC_DEC} -t 2 -b "${input_file}" -o ${TEMPFILEYUV} | grep SizeInfo | cut -d " " -f 4)
    #    echo ${resolution}
    ffmpeg -pix_fmt yuv420p10le -s ${resolution} -y -i ${TEMPFILEYUV} -pix_fmt yuv420p ${TEMPFILEYUV2}

#    ${CJPEG} 
#    convert-im6 -size ${resolution} -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV2} -quality 89 $"{output_file}"
    convert-im6 -size ${resolution} -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV2} pnm:- | ${CJPEG_ENC} -quality 95 -outfile "${output_file}"


    rm -f ${TEMPFILEYUV}
    rm -f ${TEMPFILEYUV2}

elif [ ${IMAGE_FORMAT} = "evc" ]; then

  resolution=$(${EVC_DEC} -i "${input_file}" -o ${TEMPFILEYUV} | grep Resolution| cut -f 2 -d = |  tr -d '[:space:]')

  convert-im6 -size ${resolution} -sampling-factor 4:2:0 -depth 8 -colorspace Rec709YCbCr ${TEMPFILEYUV} pnm:- | ${CJPEG_ENC} -quality 95 -outfile "${output_file}"

  rm -f ${TEMPFILEYUV}
fi
