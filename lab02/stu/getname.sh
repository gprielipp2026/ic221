#!/usr/bin/bash

if [ $# -lt 1 ]
then
  echo "Usage: $0 <user>"
  exit 0
fi

grep "^$1:" /etc/passwd | cut -d: -f5 | tr -d ','
