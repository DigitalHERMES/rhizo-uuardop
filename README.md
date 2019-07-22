# rhizo-uuardop
Tools to integrate Ardop to UUCP

RHIZO-UUARDOP is a set of tools which allow UUCP to use ARDOP as modem. With this integration, all the services which UUCP provides like email and file transfers will be able to be fully funcional over HF links using Ardop modem.

rhizo-uuardop comes with two tools: uuardopd and uuport.

UUARDOPD is the daemon which connects ARDOP and to UUPORT.

UUPORT is the commmand invoked by UUCICO (using port type = pipe) in both
master (calling) or slave mode (receiving a call).
