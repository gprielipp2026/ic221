#!/usr/bin/bash

readarray -t users < <(cat /etc/passwd | cut -d: -f5 | tr -d ',')

for i in ${!users[@]}
do

  if [[ -n "${users[$i]}" ]]
  then
    echo ${users[$i]}
  fi

done
