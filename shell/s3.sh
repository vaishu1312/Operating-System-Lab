#!/bin/bash
#math operations using case
if [ $# -ne 3 ]
then
   echo Insufficient no.of arguments
   exit 1    
fi
 case $2 in
    +) r=`expr $1 + $3` ;;
    -) r=`expr $1 - $3` ;;
    /) r=`expr $1 / $3` ;;
    X) r=`expr $1 \\* $3` ;;
 esac
echo The result of $1 $2 $3 is $r

