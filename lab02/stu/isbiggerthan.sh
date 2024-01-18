#!/usr/bin/bash

# error checking :)
if [ $# -lt 2 ]
then
  echo "ERROR: Require path and size" >&2
  exit 0
fi

if [[ $1 =~ ^[a-zA-Z]+ ]]
then
  echo "ERROR: Require a number for size" >&2
  exit 0
fi

if [[ $1 =~ ^-[0-9]+ ]]
then
  echo "ERROR: Require a positive number for size" >&2
  exit 0
fi

if [ ! -f $2 ]
then
  echo "ERROR: File $2 does not exist" >&2
  exit 0
fi

size=$(ls -l $2 | tr -s ' ' | cut -d' ' -f5)

if [ $size -gt $1 ] || [ $size -eq $1 ]
then
  echo "yes"
else
  echo "no"
fi
