#!/bin/sh

SOURCE_DIR=/fdsdfds
ENCODED_DIR=
RECONSTRUCTED_DIR=

COMPRESS_IMAGE=
DECOMPRESS_IMAGE=

cd ${CONTENT_DIR}

CODEC=vvc

mkdir -p ${ENCODED_DIR}/
mkdir -p ${RECONSTRUCTED_DIR}/

# compress data
for i in $(ls -1); do

  no_extension=${i%.*}
  ${COMPRESS_IMAGE} ${i} ${ENCODED_DIR}/{no_extension}.${CODEC}
  echo ${COMPRESS_IMAGE} ${i} ${ENCODED_DIR}/{no_extension}.${CODEC}
done

# decompress data
