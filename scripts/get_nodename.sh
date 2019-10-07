#!/bin/sh
egrep -v '^\s*#' /etc/uucp/config | grep nodename | cut -f 2
