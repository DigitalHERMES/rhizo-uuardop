/* Rhizo-HF-connector: A connector to different HF modems
 * Copyright (C) 2018 Rhizomatica
 * Author: Rafael Diniz <rafael@riseup.net>
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 *
 * Functions used by any type of modem
 */

/**
 * @file common.c
 * @author Rafael Diniz
 * @date 09 May 2018
 * @brief Common functions used by any type of modem
 *
 * Common functions used by any type of modem.
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sched.h>
#include <sys/inotify.h>

#include "common.h"

void *connection_timeout_thread(void *conn){
    rhizo_conn *connector = (rhizo_conn *) conn;

    connector->timeout_counter = 0;

    while(connector->tcp_ret_ok){

        if (connector->connected == true){
	  if (connector->safe_state == 2){
	    connector->timeout_counter++;
	  }
	  else{
	    connector->timeout_counter = 0;
	  }
	}
        else{
            connector->timeout_counter = 0;
        }
        sleep(1);
    }

    return EXIT_SUCCESS;
}

bool inotify_wait(char *file_name){
    // now starts inotify marvelous...
#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))
    int length, i = 0;
    int fd;
    int wd;
    char buffer_inot[BUF_LEN];



    fd = inotify_init();

    if (fd < 0) {
        perror("inotify_init");
    }

    wd = inotify_add_watch(fd, file_name, IN_CREATE | IN_DELETE);

    i = 0;
    length = read(fd, buffer_inot, BUF_LEN);

    if (length < 0) {
        perror("read");
    }

    while (i < length) {
        struct inotify_event *event =
            (struct inotify_event *) &buffer_inot[i];
        if (event->len) {
            if (event->mask & IN_CREATE) {
                goto exitt;
            }
            if (event->mask & IN_DELETE) {
                goto exitt;
            }
        }
            i += EVENT_SIZE + event->len;
        }

exitt:
    inotify_rm_watch(fd, wd);
    close(fd);

    sleep(1);

    return true;
}
