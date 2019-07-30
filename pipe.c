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

#include <sys/ioctl.h>
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
#include <errno.h>
#include <fcntl.h>

#include "common.h"
#include "pipe.h"

void *pipe_read_thread(void *conn)
{
    bool running;
    int num_read = 0;
    int bytes_pipe = 0;
    uint8_t buffer[BUFFER_SIZE];
    rhizo_conn *connector = (rhizo_conn *) conn;
    int input_fd;

try_again:
    inotify_wait(connector->input_pipe);
    running = true;
    fprintf(stderr, "connector->session_counter_read: %d\n", connector->session_counter_read);
    input_fd = open(connector->input_pipe, O_RDONLY);

    if (input_fd == -1)
    {
        fprintf(stderr, "pipe_read_thread: Error opening: %s\n", connector->input_pipe);
        goto try_again;
    }

    while (running)
    {
        // TODO: block until there is data available...
        ioctl(input_fd, FIONREAD, &bytes_pipe);
        if (bytes_pipe > BUFFER_SIZE)
            bytes_pipe = BUFFER_SIZE;
        if (bytes_pipe <= 0)
            bytes_pipe = 1; // so we block in read() in case of no data to read

        num_read = read(input_fd, buffer, bytes_pipe);

//        for (int k = 0; k < bytes_pipe; k++)
//            fputc(buffer[k],stderr);
//        fprintf(stderr, "\n");

//        fprintf(stderr, "Pipe read %d\n", num_read);

        if (num_read > 0)
        {
            write_buffer(&connector->in_buffer, buffer, num_read);
            continue;
        }
        if (num_read == 0)
        {
            fprintf(stderr, "pipe_read_thread: read == 0\n");
            // should we check errorno??
            running = false;
            continue;

        }
        if (num_read == -1)
        {
            fprintf(stderr, "pipe_read_thread: read() error! error no: %d\n",errno);
            running = false;
            continue;
        }
    }

    close(input_fd);
    connector->session_counter_read++;

    while(connector->session_counter_read > connector->session_counter_write)
        usleep(100000); // 0.1s

    usleep(2000000); // 2.0s // just to keep things cool

    connector->clean_buffers = true;
    goto try_again;

    return NULL;
}

void *pipe_write_thread(void *conn)
{
    bool running;
    rhizo_conn *connector = (rhizo_conn *) conn;
    int bytes_to_read = 0;
    int num_written = 0;
    uint8_t buffer[BUFFER_SIZE];
    int output_fd;

try_again:
    // fprintf(stderr, "before inotify_wait\n");
    inotify_wait(connector->output_pipe);
    running = true;
    fprintf(stderr, "connector->session_counter_write: %d\n", connector->session_counter_write);
    output_fd = open(connector->output_pipe, O_WRONLY);

    if (output_fd == -1)
    {
        fprintf(stderr, "pipe_write_thread: Error opening: %s\n", connector->input_pipe);
        goto try_again;
        // return NULL;
    }

    while (running)
    {
        bytes_to_read = ring_buffer_count_bytes(&connector->out_buffer.buf);
        if (bytes_to_read == 0)
        { // we spinlock here
            usleep(100000); // 0.1s
            if (connector->session_counter_read > connector->session_counter_write)
                running = false;
            continue;
        }

        if (bytes_to_read > BUFFER_SIZE)
            bytes_to_read = BUFFER_SIZE;

        read_buffer(&connector->out_buffer, buffer, bytes_to_read);

//        for (int k = 0; k < bytes_to_read; k++)
//            fputc(buffer[k], stderr);
//        fprintf(stderr, "\n");

        num_written = write(output_fd, buffer, bytes_to_read);

//        fprintf(stderr, "Pipe wrote %d\n", num_written);

        if (num_written == 0)
        {
            fprintf(stderr, "pipe_write_thread: write == 0\n");
        }
        if (num_written == -1)
        {
            running = false;
            if (errno == EPIPE)
            {
                fprintf(stderr, "pipe_write_thread: write() EPIPE!\n");
            }
            else
            {
                fprintf(stderr, "pipe_write_thread: write() error no: %d\n", errno);
            }
        }
    }

    close(output_fd);
    connector->session_counter_write++;

    usleep(2000000); // 2.0s // to cool down

    goto try_again;

    return NULL;
}

void pipe_fucked(int s){
    fprintf(stderr, "\nPipe fucked! We received a SIGPIPE!\n");

    // sweeet. should we do something here?
    // TODO: close the pipes here?
    // exit(EXIT_SUCCESS);
    return;
}
