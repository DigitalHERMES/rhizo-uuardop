# rhizo-uuardop
RHIZO-UUARDOP is a set of tools which allow UUCP to use ARDOP as modem. With
this integration, UUCP is fully functional over HF links using Ardop modem.

Rhizo-uuardop comes with two tools: uuardopd and uuport.

UUARDOPD is the daemon which keeps connected to ARDOP modem and properly
 receive calls (calling uucico) and initiate calls (uucico calls thought
 UUPORT pipes connection).

UUPORT is the command invoked by UUCICO (using port type = pipe) when
initiating a call (uucico master mode).

## UUARDOPD Usage

| Option | Description |
| --- | --- |
| -i input_pipe.uucp | Pipe to be read from uucico in master mode. |
| -o output_pipe.uucp | Pipe to be written to uucico in master mode. |
| -c callsign | Station Callsign (Eg: PU2HFF) |
| -d remote_callsign | Remote Station Callsign |
| -a tnc_ip_address | IP address of the TNC |
| -p tcp_base_port | TCP base port of the TNC. ARDOP uses ports tcp_base_port and tcp_base_port+1 |
| -t timeout | Time to wait before disconnect when idling |
| -f features | Enable/Disable features. Supported features: ofdm, noofdm (default: ofdm).|
| -l | Tell UUCICO to ask login prompt (default: disabled). |
| -h | Prints this help |


## UUPORT Usage

| Option | Description |
| --- | --- |
| -i input_pipe.uucp | Pipe with data written by uucico. |
| -o output_pipe.uucp | Pipe to be read by uucico. |
| -e logfile.txt | Log file (default is stderr). |
| -h | Prints this help |

### Install

To compile and install, type:

    $ make
    $ make install

### Configuration

Port configuration example at "/etc/uucp/port":

    $ port HFP
    $ type pipe
    $ command /usr/bin/uuport -e /var/log/uucp/uuport.LOG -i /tmp/uucp1.fifo -o /tmp/uucp2.fifo

 Sys configuration example of remote system at "/etc/uucp/sys" (without login prompt):

    $ system remote
    $ call-login *
    $ call-password *
    $ time any
    $ port HFP
    $ chat "" \r

 Sys configuration example of remote system at "/etc/uucp/sys" (with login prompt - should can uuardopd with "-l"):

    $ system remote
    $ call-login *
    $ call-password *
    $ time any
    $ port HFP
    $ chat "" \r\c ogin: \L word: \P

### Running uuardopd

Example of uuardop invocation (be aware that the "-i" pipe here corresponds the "-o"
pipe in uuport call, and "-o" in uuardopd corresponds to the "-i" pipe in
uuport call):

    $ uuardopd -l -i /tmp/uucp2.fifo -o /tmp/uucp1.fifo -c BB2UIT -d PP2UIT -a 127.0.0.1 -p 8515 -t 60
