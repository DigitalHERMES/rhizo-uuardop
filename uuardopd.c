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
 * @file uuardopd.c
 * @author Rafael Diniz
 * @date 10 Jul 2019
 * @brief UUCP ARDOP daemon
 *
 * UUARDOPD main C file.
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
#include <sys/socket.h>
#include <dirent.h>

#include "uuardopd.h"
#include "pipe.h"
#include "vara.h"
#include "ardop.h"

// temporary global variable to enable sockets closure
rhizo_conn *tmp_conn = NULL;

void finish(int s){
    fprintf(stderr, "\nExiting...\n");

    /* Do house cleaning work here */
    if (tmp_conn){
        if (tmp_conn->data_socket){
            shutdown(tmp_conn->data_socket, SHUT_RDWR);
            close (tmp_conn->data_socket);
        }
        if (tmp_conn->control_socket){
            shutdown(tmp_conn->control_socket, SHUT_RDWR);
            close (tmp_conn->control_socket);
        }
    }

    // TODO: close the pipes here

    exit(EXIT_SUCCESS);
}

void *modem_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;

    if (!strcmp("vara", connector->modem_type)){
        initialize_modem_vara(connector);
    }

    if (!strcmp("ardop", connector->modem_type)){
        initialize_modem_ardop(connector);
    }

    return NULL;
}

bool initialize_connector(rhizo_conn *connector){

    initialize_buffer(&connector->in_buffer, 26); // 64MB
    initialize_buffer(&connector->out_buffer, 26); // 64MB

    connector->connected = false;
    connector->waiting_for_connection = false;
    connector->tcp_ret_ok = true;
    connector->safe_state = 0;

    connector->timeout = TIMEOUT_DEFAULT;
    connector->ofdm_mode = true;
    connector->buffer_size = 0;
    return true;
}

int main (int argc, char *argv[])
{
    rhizo_conn connector;
    tmp_conn = &connector;

    initialize_connector(&connector);

    signal (SIGINT, finish);

    // Catch SIGPIPE
    // signal (SIGPIPE, pipe_fucked);
    signal(SIGPIPE, SIG_IGN); // ignores SIGPIPE...

    fprintf(stderr, "Rhizomatica's uuardopd version 0.1 by Rafael Diniz -  rafael (AT) rhizomatica (DOT) org\n");
    fprintf(stderr, "License: GPLv3+\n\n");

    connector.ofdm_mode = true;
    connector.clean_buffers = false;

    if (argc < 7)
    {
    manual:
        fprintf(stderr, "Usage modes: \n%s -r radio_modem_type -i input_pipe.uucp -o output_pipe.uucp -c callsign -d remote_callsign -a tnc_ip_address -p tcp_base_port\n", argv[0]);
        fprintf(stderr, "%s -h\n", argv[0]);
        fprintf(stderr, "\nOptions:\n");
        fprintf(stderr, " -r [ardop,vara]           Choose modem/radio type.\n");
        fprintf(stderr, " -i input_pipe.uucp          Pipe to be read from uucico.\n");
        fprintf(stderr, " -o output_pipe.uucp         Pipe to be written to uucico.\n");
        fprintf(stderr, " -c callsign                        Station Callsign (Eg: PU2HFF).\n");
        fprintf(stderr, " -d remote_callsign           Remote Station Callsign.\n");
        fprintf(stderr, " -a tnc_ip_address            IP address of the TNC,\n");
        fprintf(stderr, " -p tnc_tcp_base_port         TNC's TCP base port of the TNC. For VARA and ARDOP ports tcp_base_port and tcp_base_port+1 are used,\n");
        fprintf(stderr, " -t timeout                 Time to wait before disconnect when idling.\n");
        fprintf(stderr, " -f features                Enable/Disable features. Supported features: ofdm, noofdm.\n");
        fprintf(stderr, " -h                          Prints this help.\n");
        exit(EXIT_FAILURE);
    }

    int opt;
    while ((opt = getopt(argc, argv, "hr:i:o:c:d:p:a:t:f:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            goto manual;
            break;
        case 'c':
            strcpy(connector.call_sign, optarg);
            break;
        case 'd':
            strcpy(connector.remote_call_sign, optarg);
            break;
        case 't':
            connector.timeout = atoi(optarg);
            break;
        case 'p':
            connector.tcp_base_port = atoi(optarg);
            break;
        case 'a':
            strcpy(connector.ip_address, optarg);
            break;
        case 'r':
            strcpy(connector.modem_type, optarg);
            break;
        case 'i':
            strcpy(connector.input_pipe, optarg);
            break;
        case 'o':
            strcpy(connector.output_pipe, optarg);
            break;
        case 'f':
            if(strstr(optarg, "noofdm"))
                connector.ofdm_mode = false;
            else
                connector.ofdm_mode = true;
            break;
        default:
            goto manual;
        }
    }

    pthread_t tid[3];

    pthread_create(&tid[0], NULL, pipe_read_thread, (void *) &connector);
    pthread_create(&tid[1], NULL, pipe_write_thread, (void *) &connector);

    // pthread_create(&tid[2], NULL, modem_thread, (void *) &connector);
    modem_thread((void *) &connector);

    if (connector.tcp_ret_ok == false){
        // reconnect and call modem_thread again?
        // say something to the spool threads??
        // we cant guarantee nothing about data passed to tnc... pthread_cancel? select?
        // spool needs to re-read the input directory...
    }

    return EXIT_SUCCESS;
}
