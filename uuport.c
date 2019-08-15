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
 */

/**
 * @file uuport.c
 * @author Rafael Diniz
 * @date 14 Aug 2019
 * @brief UUCP port
 *
 * UUPORT main C file.
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
#include <errno.h>
#include <fcntl.h>

#include "uuardopd.h"
#include "uuport.h"
#include "shm.h"
#include "ring_buffer.h"

FILE *log_fd;
bool running_read;
bool running_write;

void *read_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;
    uint8_t buffer[BUFFER_SIZE];
    int bytes_to_read = 0;
    int bytes_written = 0;

    running_read = true;
    while (running_read && (connector->shutdown == false))
    {
        bytes_to_read = ring_buffer_count_bytes(&connector->out_buffer);

        if (bytes_to_read == 0)
        { // we spinlock here
            usleep(100000); // 0.1s
            continue;
        }

        if (bytes_to_read > BUFFER_SIZE)
            bytes_to_read = BUFFER_SIZE;

        read_buffer(&connector->out_buffer, buffer, bytes_to_read);

        bytes_written = write(1, buffer, bytes_to_read);

//        fprintf(log_fd, "uuport: %d bytes written to uucico\n", bytes_written);

        if (bytes_written != bytes_to_read)
        {
            fprintf(log_fd, "read_thread: bytes_written: %d != bytes_read: %d.\n", bytes_written, bytes_to_read);
            running_read = false;
            continue;
        }
        if (bytes_written == -1)
        {
            fprintf(log_fd, "read_thread: write() error no: %d\n", errno);
            running_read = false;
            continue;
        }

    }
//    connector->session_counter_read++;

    return NULL;

}

void *write_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;
    uint8_t buffer[BUFFER_SIZE];
    int bytes_to_read = 0;
    int bytes_read = 0;

    running_write = true;
    while(running_write && (connector->shutdown == false))
    {
        // workaround to make protocol 'y' work better
        if (ring_buffer_count_bytes(&connector->in_buffer) > BUFFER_SIZE / 2)
        {
            usleep(100000); // 0.1s
            bytes_to_read = 1; // slow down...
        }
        else
        {
            bytes_to_read = 512; // protocol 'y' packet size
        }

        bytes_read = read(0, buffer, bytes_to_read);

        fprintf(log_fd, "uuport: %d bytes read from uucico\n", bytes_read);

        if (bytes_read == -1)
        {
            fprintf(log_fd, "write_thread: Error in read(), errno: %d\n", errno);
            running_write = false;
            continue;
        }
        if (bytes_read == 0)
        {
            fprintf(log_fd, "write_thread: read() returned 0\n");
            running_write = false;
            continue;
        }

        while (ring_buffer_count_free_bytes(&connector->in_buffer) < bytes_read)
        {
            fprintf(log_fd, "Buffer full!\n");
            usleep(100000);
        }
        write_buffer(&connector->in_buffer, buffer, bytes_read);
    }

//    connector->session_counter_write++;

    return NULL;
}

void finish(int s){

    if (s == SIGINT)
        fprintf(log_fd, "\nSIGINT: Exiting.\n");

    if (s == SIGTERM)
        fprintf(log_fd, "\nSIGTERM: Exiting.\n");

    if (s == SIGQUIT)
        fprintf(log_fd, "\nSIGQUIT: Exiting.\n");

    if (s == SIGHUP)
    {
        fprintf(log_fd, "\nSIGHUP: running shutdown...\n");
        running_write = false;
        running_read = false;
        fflush(log_fd);
        sleep(1);
        exit(EXIT_SUCCESS); // this is not perfect... but it is what we can do now.
        return;
    }
    if (s == SIGPIPE){
        fprintf(log_fd, "\nSIGPIPE: Doing nothing.\n");
        return;
    }

    // some house keeping here?

    fclose(log_fd);
    exit(EXIT_SUCCESS);
}


int main (int argc, char *argv[])
{
    rhizo_conn *connector;

    connector = create_shm(sizeof(rhizo_conn), SYSV_SHM_KEY_STR);

    ring_buffer_connect (&connector->in_buffer, 20, SYSV_SHM_KEY_IB);
    ring_buffer_connect (&connector->out_buffer, 20, SYSV_SHM_KEY_OB);

    char log_file[BUFFER_SIZE];
    log_file[0] = 0;

    signal (SIGINT, finish);
    signal (SIGTERM, finish);
    signal (SIGQUIT, finish);
    signal (SIGHUP, finish);

    signal (SIGPIPE, finish);

//    signal (SIGPIPE, SIG_IGN); // ignores SIGPIPE...

//    fprintf(stderr, "Rhizomatica's uuport version 0.1 by Rafael Diniz -  rafael (AT) rhizomatica (DOT) org\n");
//    fprintf(stderr, "License: GPLv3+\n\n");

    if (argc < 1)
    {
    manual:
        fprintf(stderr, "Usage modes: \n%s -l logfile\n", argv[0]);
        fprintf(stderr, "%s -h\n", argv[0]);
        fprintf(stderr, "\nOptions:\n");
        fprintf(stderr, " -e logfile.txt               Log file (default is stderr).\n");
        fprintf(stderr, " -h                           Prints this help.\n");
        exit(EXIT_FAILURE);
    }

    int opt;
    while ((opt = getopt(argc, argv, "he:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            goto manual;
            break;
        case 'e':
            strcpy(log_file, optarg);
            break;
        default:
            goto manual;
        }
    }

    if (log_file[0])
    {
        log_fd = fopen(log_file, "a");
        if (log_fd == NULL)
        {
            fprintf(stderr, "Log file could not be opened: %s\n", log_file);
            fprintf(stderr, "Reverting to stderr log.\n");
            log_fd = stderr;
        }
    }
    else
    {
        log_fd = stderr;
    }


    if (connector->shutdown == true)
    {
        fprintf(stderr, "uuardopd is in shutdown state. Exiting.\n");
        return EXIT_FAILURE;
    }

    pthread_t tid;
    pthread_create(&tid, NULL, write_thread, (void *) connector);

    read_thread(connector);

    // workaround... as write_thread blocks in fd 0...
    fclose(log_fd);
    return EXIT_SUCCESS;

    // correct should be this...
    pthread_join(tid, NULL);
    return EXIT_SUCCESS;
}
