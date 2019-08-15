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
 * @file ring_buffer.h
 * @author Rafael Diniz
 * @date 14 Aug 2019
 * @brief Optimized ring-buffer implementation
 *
 * C11 Optimized ring-buffer implementation
 *
 */

#ifndef HAVE_RING_BUFFER__
#define HAVE_RING_BUFFER__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdatomic.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// C11 lock-free Ring Buffer implementation

struct ring_buffer_aux
{
    atomic_ulong count_bytes;
    atomic_ulong write_offset_bytes;
    atomic_ulong read_offset_bytes;
    atomic_flag acquire;
};

struct ring_buffer
{
    void *address;
    struct ring_buffer_aux *ctr;
};

void read_buffer(struct ring_buffer *buffer, uint8_t *buffer_out, int size);
void write_buffer(struct ring_buffer *buffer, uint8_t *buffer_in, int size);

void ring_buffer_create (struct ring_buffer *buffer, unsigned long order, key_t key);
void ring_buffer_connect (struct ring_buffer *buffer, unsigned long order, key_t key);

void ring_buffer_free (struct ring_buffer *buffer);
void *ring_buffer_write_address (struct ring_buffer *buffer);
void ring_buffer_write_advance (struct ring_buffer *buffer, atomic_ulong count_bytes);
void *ring_buffer_read_address (struct ring_buffer *buffer);
void ring_buffer_read_advance (struct ring_buffer *buffer, atomic_ulong count_bytes);
atomic_ulong ring_buffer_count_bytes (struct ring_buffer *buffer);
atomic_ulong ring_buffer_count_free_bytes (struct ring_buffer *buffer);
void ring_buffer_clear (struct ring_buffer *buffer);

// private functions
void ring_create_shm (struct ring_buffer *buffer, unsigned long order, key_t key);
void ring_connect_shm (struct ring_buffer *buffer, unsigned long order, key_t key);


#ifdef __cplusplus
};
#endif

#endif /* HAVE_RING_BUFFER__ */
