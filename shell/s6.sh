#!/bin/bash
#file exist or not
if [ $# -ne 2 ]
then
  if [ -e $1 ]
  then
    echo File $1 exists
  else
    echo File $1 does not exist
  fi
  exit 1
else
  echo Insufficient no.of arguments	
fi
