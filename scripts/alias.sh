#!/bin/bash
#read $1
#echo nome
line=$(grep -n $1 /etc/uucp/sys|cut -d ':' -f 1)
linePlus=$((line+1))
#echo $line
name=$(head -$linePlus /etc/uucp/sys|tail -1|cut -d ' ' -f 2)
echo -n $name
