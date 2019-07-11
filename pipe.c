/* Rhizo-uuardop: Tools to integrate Ardop to UUCP
 * Copyright (C) 2019 Rhizomatica
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
 * Spool directory routines
 */

/**
 * @file pipe.c
 * @author Rafael Diniz
 * @date 07 July 2019
 * @brief Pipe/fifo routines
 *
 * Pipe/fifo routines
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/inotify.h>
#include <libgen.h>

#include "pipe.h"


void *pipe_read_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;

#if 0
//read from fifo read()
    if (read == -1)
    {
        
    }
        

    write_buffer(&connector->in_buffer, buffer, read_count);
#endif

    return NULL;
}

void *pipe_write_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;


#if 0
    // open()

    int bytes_to_read = 0;
    while (1)
    {
        bytes_to_read = ring_buffer_count_bytes(&connector->out_buffer.buf);
        if (bytes_to_read == 0)
            bytes_to_read = 1; // we lock when there is no data...
        if (bytes_to_read > BUF_SIZE)
            bytes_to_read = BUF_SIZE;

        read_buffer(&connector->out_buffer, buffer, bytes_to_read);

// write to fifo // write()
        if (written == -1 && errno == EPIPE)
        {
            break;
        }
    }
    // close()
#endif
    return NULL;
}

void pipe_fucked(int s){
    fprintf(stderr, "\nPipe fucked!\n");

    // TODO: close the pipes here?

    // exit(EXIT_SUCCESS);
    return;
}
