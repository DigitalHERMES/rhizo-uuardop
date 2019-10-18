#!/bin/bash
# uso:
# decrypt.sh arquivo_para_cifrar.gpg

if [ $# -lt 3 ]; then
  echo "Usage: $0 filename.gpg filename password"
  echo "Output: filename"
  exit 1
fi

# dec_file=$(dirname "${1}")/$(basename ${1} .gpg)

gpg -o "${2}" -d --batch --passphrase "${3}" --yes "${1}"
