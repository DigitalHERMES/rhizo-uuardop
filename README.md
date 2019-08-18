# rhizo-uuardop
RHIZO-UUARDOP is a set of tools which allow UUCP to use ARDOP as modem. With
this integration, UUCP is fully functional over HF links using Ardop modem.

Rhizo-uuardop comes with two tools: uuardopd and uuport.

UUARDOPD is the daemon which keeps connected to ARDOP modem and properly
 receive calls (calling uucico) and initiate calls (uucico calls thought
 UUPORT connection).

UUPORT is the command invoked by UUCICO (using port type = pipe) when
initiating a call (uucico master mode).

## UUARDOPD Usage

| Option | Description |
| --- | --- |
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
| -c system_name | Name of the remote system (default is don't change). |
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
    $ command /usr/bin/uuport

An alternative Port configuration if you use a patched uucp ( for "\Z"
support, available in "improved-pipe.patch" which was added to uucp debian 
package version 1.07-27 ), where uuport
sets the callsign of the station to be called from uucp remote
station name (allowing a single uuardopd instance to be used for different
remote station callsigns):

    $ port HFP
    $ type pipe
    $ command /usr/bin/uuport -c \Z

Sys protocol example (tested and works fine) at "/etc/uucp/sys":

    $ protocol y
    $ protocol-parameter y packet-size 512
    $ protocol-parameter y timeout 540
    $ chat-timeout 100

Sys configuration example of remote system at "/etc/uucp/sys" (without login prompt):

    $ system remote
    $ call-login *
    $ call-password *
    $ time any
    $ port HFP
    $ chat "" \r

 Sys configuration example of remote system at "/etc/uucp/sys" (with login prompt - should call uuardopd with "-l"):

    $ system remote
    $ call-login *
    $ call-password *
    $ time any
    $ port HFP
    $ chat "" \r\c ogin: \L word: \P

### Running uuardopd

Example of uuardopd invocation:

    $ uuardopd -l -c BB2UIT -d PP2UIT -a 127.0.0.1 -p 8515 -t 60
