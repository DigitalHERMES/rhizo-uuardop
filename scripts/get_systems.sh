#!/bin/sh

#egrep -v '^\s*#' /etc/uucp/sys | grep system | cut -f 2 -d " "
egrep -v '^\s*#' /etc/uucp/sys | grep alias | cut -f 2 -d " "
