#!/bin/bash
#biggest of 3 nos

if [ $# -ne 3 ]
then
   echo Insufficient no.of arguments
   exit 1    
fi
   n1=$1
   n2=$2
   n3=$3

   if [ $n1 -gt $n2 ] && [ $n1 -gt $n3 ]
   then
	echo  $n1 is the greatest number
   elif [ $n2 -gt $n1 ] && [ $n2 -gt $n3 ]         
   then
       echo $n2 is the greatest number
   else
       echo  $n3 is the greatest number
   fi    
