/* Rhizo-connector: A connector to different HF modems
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
 * Buffer routines
 */

/**
 * @file buffer.h
 * @author Rafael Diniz
 * @date 12 Apr 2018
 * @brief Buffer support functions
 *
 * Buffer auxiliary funtions.
 *
 */

#ifndef HAVE_BUFFER_H__
#define HAVE_BUFFER_H__

#include <stdint.h>
#include <pthread.h>

#include "ring_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    pthread_mutex_t    mutex;
    pthread_cond_t     cond;
    struct ring_buffer buf;
} buffer;

extern void read_buffer(buffer *buf_in, uint8_t *buffer_out, int size);
extern void write_buffer(buffer *buf_out, uint8_t *buffer_in, int size);
void initialize_buffer(buffer *buf, int mag);

#ifdef __cplusplus
};
#endif

#endif /* HAVE_BUFFER__ */
