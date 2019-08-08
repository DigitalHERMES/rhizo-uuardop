# some examples

# run ardop in a also loopback device:
ardop1ofdm 8515 hw:1,0 hw:1,0
ardop1ofdm 8517 hw:1,1 hw:1,1

# example ~/.asoundrc
pcm.aloop {
          type hw
          card 0
       }

ctl.aloop {
          type hw
          card 0
       }
##


# run as root (example):
uuardopd  -i /tmp/uucp2.fifo -o /tmp/uucp1.fifo -c BB2UIT -d PP2UIT -a 127.0.0.1 -p 8515 -t 60

# for job status:
uustat -a

# for killing a job:
uustat -k job_name

# to send a file:
uucp ginga.txt remote\!\~/ginga.txt

# or
uuto FILE central\!


#for sending a file:
uucp TODO central\!centrauser\!/TODO

