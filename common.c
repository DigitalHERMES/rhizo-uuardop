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
