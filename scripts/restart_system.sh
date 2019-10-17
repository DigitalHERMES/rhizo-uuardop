#!/bin/sh

sudo systemctl stop uuardopd
sudo systemctl stop ardop
sleep 1
sudo systemctl start ardop
sudo systemctl start uuardopd
