#!/bin/bash
#pattern
for i in {0..5} 
#(( i=0;i<5;i++ ))
do
  for (( j=0;j<i+1;j++ ))
  do
     echo -n "* "
  done
  echo " "
#echo -e "\n"
done

echo -e "\n"

n=9
for ((i=1;i<=n;i++))
do
  for ((j=n;j>=i;j--))
  do
    echo -n " "
  done
  for ((k=1;k<=i;k++ ))
  do
     echo -n "$i " 
  done
  echo " "
done

