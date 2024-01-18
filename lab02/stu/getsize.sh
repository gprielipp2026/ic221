#!/usr/bin/bash

if [ $# -lt 1 ]
then
  echo "Usage: $0 <file>"
  exit 0
fi

if [ ! -f $1 ]
then
  echo "ERROR: File $1 does not exist" >&2
  exit 0
fi

ls -l $1 | tr -s ' ' | cut -d' ' -f5
