#!/bin/sh

egrep -v '^\s*#' /etc/uucp/sys | grep system | cut -f 2 -d " "
