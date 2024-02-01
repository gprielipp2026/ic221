#!/bin/bash

function gen_num() {
  front="$(tr -c -d 1-9 < /dev/random | fold -w1 | head -1)" 
  end="$(tr -c -d 0-9 < /dev/random | fold -w15 | head -1)"
  echo $front$end
}

while [ 1 ]
do
  tst=$(gen_num)
  rc=$(./check $tst)
  if [ $? -eq 0 ]
  then
    echo $tst
    exit 0
  fi
done
