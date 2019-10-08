# Rhizo-uuardop: UUCP <-> Ardop tools
# Copyright (C) 2019 Rhizomatica
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


PREFIX=/usr
CC=gcc
CFLAGS=-g -Wall -std=gnu11 -pthread

all: uuardopd uuport

%.o : %.c %.h
	gcc -c $(CFLAGS) $< -o $@

uuardopd: ardop.o shm.o common.o net.o ring_buffer.o uuardopd.o call_uucico.o
	$(CC) $(CFLAGS) -o $@ $^

uuport: uuport.o shm.o ring_buffer.o
	$(CC) $(CFLAGS) -o $@ $^

install: uuardopd uuport
	install uuardopd $(PREFIX)/bin
	install uuport $(PREFIX)/bin
	install initscripts/uuardopd.service /etc/systemd/system
	install scripts/compress_image.sh $(PREFIX)/bin
	install scripts/get_nodename.sh $(PREFIX)/bin
	install scripts/get_systems.sh $(PREFIX)/bin
	install scripts/kill_job.sh $(PREFIX)/bin
	install gui/* /var/www/html/
doc:
	doxygen doxyfile

clean:
	rm -rf uuardopd uuport *.o *~ doc
