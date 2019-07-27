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
 * @file pipe.h
 * @author Rafael Diniz
 * @date 10 Jul 2019
 * @brief Pipe/fifo routines
 *
 * Pipe/fifo routines
 *
 */

#ifndef HAVE_PIPE_H__
#define HAVE_PIPE_H__

#include <stdint.h>
#include "uuardopd.h"

#ifdef __cplusplus
extern "C" {
#endif

void *pipe_read_thread(void *conn);
void *pipe_write_thread(void *conn);
void pipe_fucked(int s);

#endif /* HAVE_PIPE__ */
