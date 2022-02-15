#!/bin/bash


# sec between each call
DELAY=2

while true
do
    hosts=($(curl -s http://localhost/api/caller/ | jq --raw-output '.[0] | .stations[] | @sh' ))
    timers_start=($(curl -s http://localhost/api/caller | jq --raw-output '.[] | select( .enable | contains(1)) | .starttime ' ))
    timers_stop=($(curl -s http://localhost/api/caller | jq --raw-output '.[] | select( .enable | contains(1)) | .stoptime ' ))

    run_at_least_once=0

    for (( c=0; c<${#timers_start[@]}; c++ )); do

	      start_time_hour=$(echo ${timers_start[c]} | cut -d ':' -f 1)
	      start_time_minute=$(echo ${timers_start[c]} | cut -d ':' -f 2)
	      end_time_hour=$(echo ${timers_stop[c]} | cut -d ':' -f 1)
	      end_time_minute=$(echo ${timers_stop[c]} | cut -d ':' -f 2)

	      current_hour=$(date +%H)
	      current_minute=$(date +%M)

	      echo "Schedule " $c
	      echo "current time ${current_hour}h ${current_minute}min"
	      echo "start time ${start_time_hour}h ${start_time_minute}min"
	      echo "end time ${end_time_hour}h ${end_time_minute}min"

	      if [[ ${current_hour} -eq ${start_time_hour} &&
		              ${current_minute} -ge ${start_time_minute} ]] ||
               [[ ${current_hour} -gt ${start_time_hour} &&
		                  ${current_hour} -lt ${end_time_hour} ]] ||
               [[ ${current_hour} -eq ${end_time_hour} &&
                      ${current_minute} -le ${end_time_minute} ]]

	      then

                  run_at_least_once=1
	          for t in ${hosts[*]}; do
		            echo "Calling ${t}"
		            # uucico -S ${t}
		            sleep ${DELAY}
	          done

	      else
	          echo "Schedule ${c} will not run now."
	          echo
	      fi

    done

    if [[ ${run_at_least_once} -eq 0 ]]
    then
      sleep ${DELAY}
    fi

done
