#!/bin/bash

start_time_hour=9
start_time_minute=30

end_time_hour=20
end_time_minute=30

# 30sec between each call
DELAY=30

HOSTS="ac1 ac3 ac4 ac5 ac6 ac7 ac9"

current_hour=$(date +%H)
current_minute=$(date +%M)

while [[ ${current_hour} -eq ${start_time_hour} &&
           ${current_minute} -ge ${start_time_minute} ]] ||
        [[ ${current_hour} -gt ${start_time_hour} &&
             ${current_hour} -lt ${end_time_hour} ]] ||
              [[ ${current_hour} -eq ${end_time_hour} &&
                   ${current_minute} -le ${end_time_minute} ]]

do

  echo "current time ${current_hour}h ${current_minute}min"
  echo "start time ${start_time_hour}h ${start_time_minute}min"
  echo "end time ${end_time_hour}h ${end_time_minute}min"
  echo

  for t in ${HOSTS}; do
    echo "Calling ${t}"
    uucico -S ${t}
    sleep ${DELAY}
  done

  current_hour=$(date +%H)
  current_minute=$(date +%M)

done
