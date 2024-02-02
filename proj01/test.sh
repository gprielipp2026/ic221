#!/bin/bash


readarray -t tests <<<"$(cut -d, testcases.txt -f1)"
readarray -t answs <<<"$(cut -d, testcases.txt -f2)"

#IFS=$'\n' read -rd '' -a tests <<<"$(cut -d, testcases.txt -f2)"

#tests=( $(cut -d, testcases.txt -f1) )

#IFS=$'\n' mapfile  tests < testcases.txt


for i in $(seq 1 ${#tests[@]})
do
  res=$(eval ${tests[i]} | tr '\n' ' ')
  
# compare it to the results
  if [[ "$res" != *"${answs[i]}"* ]]
  then
    echo "FAILED: '${tests[i]}'"
  fi
done
