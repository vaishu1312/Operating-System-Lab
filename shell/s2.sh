#!/bin/bash
#print 5,4,3,2,1
i=5
while [ $i -ge 1 ]
do
 echo $i
 i=$(( i-1 ))
#i=`expr $i - 1`
done

