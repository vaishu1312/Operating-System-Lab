if [ $# -ne 3 ] 
then
echo Insufficient no. of arguments
exit 1
fi

if [ -e $3 ]; 
  then
     tail -n +$1 $3 | head -n $2
else
   echo "Error opening file" 
fi 

