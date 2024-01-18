#!/usr/bin/bash

readarray -t users < <(cat /etc/passwd | cut -d: -f5 | tr -d ',')
declare -p users

for i in ${!users[@]}
do

  if [[ -n "${user[$i]}" ]]
  then
    echo ${user[$i]}
  fi

done
