#!/bin/bash
# uso:
# decrypt.sh arquivo_para_cifrar.gpg

if [ $# -lt 2 ]; then
  echo "Usage: $0 filename.gpg password"
  echo "Output: filename"
  exit 1
fi

dec_file=$(dirname "${1}")/$(basename ${1} .gpg)

gpg -o "${dec_file}" -d --batch --passphrase "${2}" --yes "${1}"
