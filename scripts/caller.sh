#!/bin/bash

DELAY=2

HOSTS=(ac1 ac2 ac3 ac4 ac5 ac6 ac7)

for t in ${HOSTS[@]}; do
          echo uucico -r1 $t
          #uucico -r1 $t
          sleep $DELAY
done
