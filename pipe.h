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
 */

/**
 * @file spool.h
 * @author Rafael Diniz
 * @date 12 Apr 2018
 * @brief Spool directory routines
 *
 * Spool directory routines
 *
 */

#ifndef HAVE_PIPE_H__
#define HAVE_PIPE_H__

#include <stdint.h>
#include "uuardopd.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE 8192

void *spool_output_directory_thread(void *conn);
void *spool_input_directory_thread(void *conn);
bool queue_msg_path(char *msg_path, rhizo_conn *connector);
bool remove_all_msg_path_queue(rhizo_conn *connector);

#endif /* HAVE_PIPE__ */
