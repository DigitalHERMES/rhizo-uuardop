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


/** @brief Queue a message path to the list of sent message paths
 *         (waiting for an ack to be deleted)
 *
 *  @param msg_path Message path.
 *  @param connector Connector handle.
 *  @return bool Returns true in case of success.
 */
bool queue_msg_path(char *msg_path, rhizo_conn *connector){

    pthread_mutex_lock(&connector->msg_path_queue_mutex);

    connector->msg_path_queue[connector->msg_path_queue_size] = (char *) malloc(strlen(msg_path)+1);
    strcpy(connector->msg_path_queue[connector->msg_path_queue_size], msg_path);
    connector->msg_path_queue_size++;

    pthread_mutex_unlock(&connector->msg_path_queue_mutex);

    return true;

}

bool remove_all_msg_path_queue(rhizo_conn *connector){
    pthread_mutex_lock(&connector->msg_path_queue_mutex);

    for(int i = 0; i < connector->msg_path_queue_size; i++){
        if (unlink(connector->msg_path_queue[i]) != 0){
            fprintf(stderr, "File %s could not be deleted!\n", connector->msg_path_queue[i]);
        }
        free(connector->msg_path_queue[i]);
    }
    connector->msg_path_queue_size = 0;
    // add path to connector->msg_path_queue
    pthread_mutex_unlock(&connector->msg_path_queue_mutex);

    return true;

}

bool write_message_to_buffer(char *msg_path, rhizo_conn *connector){
    uint8_t buffer[BUFFER_SIZE];
    char *base_path;
    FILE *f_in;
    uint32_t msg_size;
    uint32_t msg_path_size = 0;

    f_in = fopen(msg_path,"r");
    if (f_in == NULL){
        fprintf(stderr, "write_message_to_buffer: Message %s could not be opened.\n", msg_path);
        return false;
    }

    struct stat st;
    stat(msg_path, &st);
    msg_size = (uint32_t) st.st_size;

    base_path = basename(msg_path);

    fprintf(stderr, "Loaded message %s with payload size %u.\n", base_path, msg_size);

    msg_path_size = strlen(base_path)+1;
    msg_size += msg_path_size;
    base_path[msg_path_size-1] = '\n'; // adding a \n to the 0 in the string (just to make the message clear over the air)

    // our 4 byte header which contains the size of the message
    write_buffer(&connector->in_buffer, (uint8_t *) &msg_size, sizeof(msg_size));

    // the file path basename
    write_buffer(&connector->in_buffer, (uint8_t *) base_path, msg_path_size);

    size_t read_count = 0;
    uint32_t total_read = 0;
    while ((read_count = fread(buffer, 1, sizeof(buffer), f_in)) > 0){
        total_read += read_count;

        // fprintf(stderr, "writing to buffer msg of size %u tx now: %lu\n", msg_size, read_count);
        write_buffer(&connector->in_buffer, buffer, read_count);
    }

    if (total_read + msg_path_size != msg_size){
        fprintf(stderr, "Warning: possible truncated message. FIXME! total_read = %u msg_size = %u\n", total_read + msg_path_size, msg_size);
    }

    fclose(f_in);

    base_path[msg_path_size-1] = 0; // reverting to a null terminated string
    queue_msg_path(msg_path, connector);

    return true;
}

bool read_message_from_buffer(rhizo_conn *connector){
    char msg_path[1024];
    int index = 0;
    char ch;
    uint32_t msg_size = 0;
    uint8_t buffer[BUFFER_SIZE];

    read_buffer(&connector->out_buffer, (uint8_t *) &msg_size, sizeof(msg_size));

    strcpy(msg_path, connector->output_directory);
    do {
        read_buffer(&connector->out_buffer, (uint8_t *) &ch, 1);
        msg_path[strlen(connector->output_directory)+index] = ch;
        index++;
    } while(ch != '\n'); // TODO read from buffer the filename....

    msg_path[strlen(connector->output_directory)+index-1] = 0;

    msg_size -= index;

    fprintf(stderr, "Incoming message %s with payload size %u.\n", basename(msg_path), msg_size);

    FILE *fp = fopen (msg_path, "w");
    if (fp == NULL){
        fprintf(stderr, "read_message_from_buffer: Message %s could not be opened.\n", msg_path);
        return false;
    }

    uint32_t counter = msg_size;
    while (counter != 0){
#if 1
        read_buffer(&connector->out_buffer, buffer, 1);
        fwrite(buffer, 1, 1, fp);
        counter--;
//        fprintf(stderr, "%c", buffer[0]);
#else
        if (counter > BUFFER_SIZE){
            read_buffer(&connector->out_buffer, buffer, BUFFER_SIZE);
            fwrite(buffer, 1, BUFFER_SIZE, fp);
            counter -= BUFFER_SIZE;
        }
        else{
            read_buffer(&connector->out_buffer, buffer, counter);
            fwrite(buffer, 1, counter, fp);
            counter -= counter;
        }
#endif
//        fprintf(stderr, "rx counter: %u\n", counter);
    }

    fclose(fp);

    return true;
}

void *spool_output_directory_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;

    DIR *dirp = opendir(connector->output_directory);
    if (dirp == NULL){
        fprintf(stderr, "Directory \"%s\" could not be opened.\n", connector->output_directory);
        return NULL;
    }
    closedir(dirp);

    while (true){
        read_message_from_buffer(connector);
    }

    return NULL;
}

void *spool_input_directory_thread(void *conn)
{
    rhizo_conn *connector = (rhizo_conn *) conn;
    struct dirent *dp;
    char msg_path[1024];

    DIR *dirp = opendir(connector->input_directory);
    if (dirp == NULL){
        fprintf(stderr, "Directory \"%s\" could not be opened.\n", connector->input_directory);
        return NULL;
    }
    while ((dp = readdir(dirp)) != NULL){
        if (dp->d_type == DT_REG){
            strcpy(msg_path, connector->input_directory);
            strcat(msg_path, dp->d_name);
            write_message_to_buffer(msg_path, connector);
        }
    }
    closedir(dirp);


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

    wd = inotify_add_watch(fd, connector->input_directory,
                           IN_MOVED_TO | IN_CLOSE_WRITE);

    while(true){
        i = 0;
        length = read(fd, buffer_inot, BUF_LEN);

        if (length < 0) {
            perror("read");
        }

        while (i < length) {
            struct inotify_event *event =
                (struct inotify_event *) &buffer_inot[i];
            if (event->len) {
                if ((event->mask & IN_CLOSE_WRITE) || (event->mask & IN_MOVED_TO)) {
                    strcpy(msg_path, connector->input_directory);
                    strcat(msg_path, event->name);
                    write_message_to_buffer(msg_path, connector);
                }


            }
            i += EVENT_SIZE + event->len;
        }

    }
    inotify_rm_watch(fd, wd);
    close(fd);

    fprintf(stderr, "Spool is finishing...\n");

    return NULL;
}
