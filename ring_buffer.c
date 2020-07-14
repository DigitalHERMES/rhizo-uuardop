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
 * @file ring_buffer.c
 * @author Rafael Diniz
 * @date 14 Aug 2019
 * @brief Optimized ring-buffer implementation
 *
 * C11 Optimized ring-buffer implementation
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <malloc.h>

#include "ring_buffer.h"
#include "shm.h"

void read_buffer(struct ring_buffer *buffer, uint8_t *buffer_out, int size)
{
    void *addr;

    while (ring_buffer_count_bytes(buffer) < size)
    {
        usleep(10000); // 10ms
    }

    while (atomic_flag_test_and_set(&buffer->ctr->acquire));

    addr = ring_buffer_read_address(buffer);
    memcpy(buffer_out, addr, size);
    ring_buffer_read_advance(buffer, size);
    atomic_flag_clear(&buffer->ctr->acquire);
}

void write_buffer(struct ring_buffer *buffer, uint8_t *buffer_in, int size)
{
    void *addr;

    while (ring_buffer_count_free_bytes(buffer) < size)
    {
        usleep(10000); // 10ms
    }

    while (atomic_flag_test_and_set(&buffer->ctr->acquire));

    addr = ring_buffer_write_address(buffer);
    memcpy(addr, buffer_in, size);
    ring_buffer_write_advance(buffer, size);
    atomic_flag_clear(&buffer->ctr->acquire);
}


void ring_buffer_create (struct ring_buffer *buffer, unsigned long order, key_t key)
{
    buffer->ctr = create_shm(sizeof(struct ring_buffer_aux), key+1);

    if (buffer->ctr == NULL)
    {
        abort();
    }

    buffer->ctr->count_bytes = 1UL << order;
    buffer->ctr->write_offset_bytes = 0;
    buffer->ctr->read_offset_bytes = 0;
    atomic_flag_clear(&buffer->ctr->acquire);

    ring_create_shm (buffer, order, key);
}

void ring_buffer_connect (struct ring_buffer *buffer, unsigned long order, key_t key)
{
    void *addr;
    addr = connect_shm(sizeof(struct ring_buffer_aux), buffer->ctr, key+1);

    if (addr == NULL)
    {
        abort();
    }

    ring_connect_shm (buffer, order, key);
}


void ring_create_shm (struct ring_buffer *buffer, unsigned long order, key_t key)
{
    void *address;
    int shmid;

    address = memalign(4*sysconf(_SC_PAGESIZE), buffer->ctr->count_bytes << 1);

    /*  create the segment */
    if ((shmid = shmget(key, buffer->ctr->count_bytes, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
    {
        if (errno != EEXIST)
        {
            // fprintf(stderr, "Error creating Shm memory segment.\n");
            abort();
        }

        // fprintf(stderr, "Shm memory segment already created, attaching.\n");

        if ((shmid = shmget(key, buffer->ctr->count_bytes, 0)) == -1)
        {
            // fprintf(stderr, "Error creating attaching to shm memory segment.\n");
            abort();
        }
    }

    /* attach to the segment to get a pointer to it: */
    buffer->address = shmat(shmid, address, SHM_REMAP);
    if (buffer->address == (void *) -1) {
        // fprintf(stderr, "Error in shmat with shm.\n");
        abort();
    }

    if (address != buffer->address){
        // fprintf(stderr, "Error in shmat addr != addr.\n");
        abort();
    }

    address = shmat(shmid, address + buffer->ctr->count_bytes, SHM_REMAP);

    if (address == (void *) -1) {
        // fprintf(stderr, "Error in shmat with shm.\n");
        abort();
    }

    if (address != buffer->address + buffer->ctr->count_bytes){
        // fprintf(stderr, "Error in buffer madness.\n");
        abort();
    }

}

void ring_connect_shm (struct ring_buffer *buffer, unsigned long order, key_t key)
{
    int shmid;
    void *ret_address;

    ret_address = mmap(buffer->address, buffer->ctr->count_bytes << 1, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED,
                       -1, 0);

    if (ret_address != buffer->address){
        // fprintf(stderr, "Error creating in mmap.\n");
        abort();
    }

    /*  create the segment */
    if ((shmid = shmget(key, buffer->ctr->count_bytes, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
    {
        if (errno != EEXIST)
        {
            // fprintf(stderr, "Error creating Shm memory segment.\n");
            abort();
        }

        // fprintf(stderr, "Shm memory segment already created, attaching.\n");

        if ((shmid = shmget(key, buffer->ctr->count_bytes, 0)) == -1)
        {
            // fprintf(stderr, "Error creating attaching to shm memory segment.\n");
            abort();
        }
    }

    /* attach to the segment to get a pointer to it: */
    ret_address = shmat(shmid, buffer->address, SHM_REMAP);
    if (ret_address == (void *) -1) {
        // fprintf(stderr, "Error in shmat with shm.\n");
        abort();
    }

    if (ret_address != buffer->address){
        // fprintf(stderr, "Error in shmat addr != addr.\n");
        abort();
    }

    ret_address = shmat(shmid, buffer->address + buffer->ctr->count_bytes, SHM_REMAP);

    if (ret_address == (void *) -1) {
        // fprintf(stderr, "Error in shmat with shm.\n");
        abort();
    }

    if (ret_address != buffer->address + buffer->ctr->count_bytes){
        // fprintf(stderr, "Error in buffer madness.\n");
        abort();
    }

}


void ring_buffer_free (struct ring_buffer *buffer)
{
    int status;

    status = shmdt(buffer->address);
    if (status){
        // fprintf(stderr, "Error in ring_buffer_free.\n");
        abort();
    }

    status = shmdt(buffer->address + buffer->ctr->count_bytes);
    if (status){
        // fprintf(stderr, "Error in ring_buffer_free.\n");
        abort();
    }

    // free and munmap also?

}

void *ring_buffer_write_address (struct ring_buffer *buffer)
{
    return buffer->address + buffer->ctr->write_offset_bytes;
}

void ring_buffer_write_advance (struct ring_buffer *buffer,
                           atomic_ulong count_bytes)
{
  buffer->ctr->write_offset_bytes += count_bytes;
}

void *ring_buffer_read_address (struct ring_buffer *buffer)
{
    return buffer->address + buffer->ctr->read_offset_bytes;
}

void ring_buffer_read_advance (struct ring_buffer *buffer,
                          atomic_ulong count_bytes)
{
  buffer->ctr->read_offset_bytes += count_bytes;

  if (buffer->ctr->read_offset_bytes >= buffer->ctr->count_bytes)
  {
      buffer->ctr->read_offset_bytes -= buffer->ctr->count_bytes;
      buffer->ctr->write_offset_bytes -= buffer->ctr->count_bytes;
  }
}

atomic_ulong ring_buffer_count_bytes (struct ring_buffer *buffer)
{
  return buffer->ctr->write_offset_bytes - buffer->ctr->read_offset_bytes;
}

atomic_ulong ring_buffer_count_free_bytes (struct ring_buffer *buffer)
{
  return buffer->ctr->count_bytes - ring_buffer_count_bytes (buffer);
}

void ring_buffer_clear (struct ring_buffer *buffer)
{
  buffer->ctr->write_offset_bytes = 0;
  buffer->ctr->read_offset_bytes = 0;
}
