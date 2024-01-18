#!/usr/bin/bash

# check inputs
if [[ $# -lt 2 ]]
then
  echo "ERROR: Require a size and at least one file" >&2
  exit 1
fi

#check number
if [[ $1 =~ ^[a-zA-Z]+ ]] 
then
  echo "ERROR: Require a number for size" >&2
  exit 2
fi

# check positive
if [[ $1 =~ ^-[0-9]+ ]]
then
  echo "ERROR: Require a positive number for size" >&2
  exit 3
fi

for path in ${@:2}
do
  if [[ ! -f $path ]]
  then
    echo "ERROR: File $path does not exist" >&2
  else
    size=$(ls -l $path | tr -s ' ' | cut -d' ' -f5)
    if [[ $size -gt $1 ]] || [[ $size -eq $1 ]]
    then
      echo $path
    fi
  fi
done

