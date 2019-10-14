#!/bin/bash

systemctl stop uuardopd
systemctl stop ardop
sleep 1
systemctl start ardop
sleep 1
systemctl start uuardopd
