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
 * Routines to call uucico when receiving a call
 */

/**
 * @file call_uucico.c
 * @author Rafael Diniz
 * @date 26 Jul 2019
 * @brief Routines to call uucico when receiving a call
 *
 * Code to call uucico
 *
 */

#include "call_uucico.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <grp.h>

bool call_uucico(rhizo_conn *connector){
    pid_t pid;
    int st;
    // set some file descriptors as in in.uucpd...
    // use 2 pipe() to create the fds for I/O
    // fork()
    // in the parent, call wait to wait for uucico (in a new thread?)
    // in the child, remap the fds to 0, 1 (and 2?) 
    // in the child, call execl() (or execlp() (uucico -l)

    // parent
    if ((pid = fork()) != 0)
    {
        if (pid < 0) {
            /* FIXME: SCREAM (oh well..) */
            return false;
        }
        while(wait(&st) != pid);
        if ( WIFEXITED(st) ){
            fprintf(stderr, "uucico child exec exited with status = %d\n", WEXITSTATUS(st));
            // uucico ended!
            // we should disconnect here!
        }
        return true;
    }

    // this is the child
    signal(SIGHUP, SIG_DFL);
    char pwd[] = "/var/spool/uucp"; // uucp home
    if (chdir(pwd) != 0) {
        perror(pwd);
        exit(1);
    }
    gid_t gid = 10; // uucp gid
    if (setgid(gid) != 0) {
        perror("setgid");
        exit(1);
    }
    char user[] = "uucp";
    if (initgroups(user, gid) < 0) {
        perror("initgroups");
        exit(1);
    }
    uid_t uid = 10; // uucp uid
    if (setuid(uid) != 0) {
        perror("setuid");
        exit(1);
    }

    char shell[] = "/usr/sbin/uucico";

    setenv("LOGNAME", user, 1);
    setenv("USER", user, 1);
    setenv("SHELL", shell, 1);
    setenv("TERM", "dumb", 1);


    execl(shell, shell, "-l", NULL);
    perror(shell);


    return true;
}

void *uucico_read_thread(void *conn) {
    rhizo_conn *connector = (rhizo_conn *) conn;

}


void *uucico_write_thread(void *conn) {
    rhizo_conn *connector = (rhizo_conn *) conn;

}
