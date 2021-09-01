#!/bin/sh

quality="40k"

echo "<html>"

echo "<head><title>Avaliação de qualidade</title></head>"

echo "<body>"

for i in *; do

  input_file=\"${i}\"
  no_extension=${i%.*}

  size=$(stat -c%s "../encoded-vvc-${quality}/${no_extension}.vvc")

  echo "Size: ${size}<br /><img src=${input_file} /> <br /> <br />"

done

echo "</body>"
echo "</html>"
