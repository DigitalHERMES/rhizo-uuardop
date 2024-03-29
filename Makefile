# Rhizo-uuardop: UUCP <-> HF tools
# Copyright (C) 2019-2021 Rhizomatica
# Author: Rafael Diniz <rafael@riseup.net>
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#


prefix=/usr
CC=gcc
CFLAGS=-g -Wall -pedantic -std=gnu11 -pthread -fstack-protector


all: uuardopd uuport

%.o : %.c %.h
	gcc -c $(CFLAGS) $< -o $@

uuardopd: ardop.o shm.o common.o net.o circular_buffer.o uuardopd.o call_uucico.o serial.o vara.o
	$(CC) $(CFLAGS) -o $@ $^

uuport: uuport.o shm.o circular_buffer.o
	$(CC) $(CFLAGS) -o $@ $^


.PHONY: clean install doc
install: uuardopd uuport
	install -D uuardopd $(DESTDIR)$(prefix)/bin/uuardopd
	install -D uuport $(DESTDIR)$(prefix)/bin/uuport
	install -m 644 -D initscripts/uuardopd.service $(DESTDIR)/etc/systemd/system/uuardopd.service
	install scripts/vara_watchdog.sh $(DESTDIR)$(prefix)/bin

install_gateway: install
	install -m 644 -D initscripts/caller.service $(DESTDIR)/etc/systemd/system/caller.service
	install scripts/caller.sh $(DESTDIR)$(prefix)/bin

doc:
	doxygen doxyfile

clean:
	rm -rf uuardopd uuport *.o *~ doc
