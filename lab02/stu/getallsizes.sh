#/usr/bin/bash

if [ $# -lt 1 ]
then
  echo "Usage: $0 <pattern?> <files?>"
  exit 0
fi

for file in $@
do
  if [ ! -f $file ]
  then
    echo "ERROR: File $file does not exist" >&2
  else
    # do the thing!
    echo -n $file 
    size=$(ls -l $file | tr -s ' ' | cut -d' ' -f5)
    echo " $size"
  fi
done
