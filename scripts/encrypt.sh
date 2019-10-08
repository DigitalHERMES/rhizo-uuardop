#!/bin/bash
# uso:
# encrypt.sh arquivo_para_cifrar.abc

if [ $# -lt 2 ]; then
  echo "Usage: $0 filename password"
  echo "Output: filename.gpg"
  exit 1
fi

enc_file="${1}.gpg"

gpg -o "${enc_file}" --symmetric --cipher-algo AES256 --batch --passphrase "${2}" --yes "${1}"

rm "${1}"
