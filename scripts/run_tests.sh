#!/bin/sh

CODEC=vvc

SOURCE_DIR=/root/content/images
ENCODED_DIR=/root/content/encoded-vvc
RECONSTRUCTED_DIR=/root/content/reconstructed-vvc

COMPRESS_IMAGE=/home/hermes/rhizo-uuardop/scripts/compress_image.sh
DECOMPRESS_IMAGE=/home/hermes/rhizo-uuardop/scripts/decompress_image.sh

cd ${SOURCE_DIR}

mkdir -p ${ENCODED_DIR}/
mkdir -p ${RECONSTRUCTED_DIR}/

# compress data
for i in *; do

    no_extension=${i%.*}
    
#    input_file=\"${i}\"
#    output_file=\"${ENCODED_DIR}/${no_extension}.${CODEC}\"
#    echo compress ${COMPRESS_IMAGE} ${input_file} ${output_file}
    eval ${COMPRESS_IMAGE} \"${i}\" \"${ENCODED_DIR}/${no_extension}.${CODEC}\"

done

# decompress data
