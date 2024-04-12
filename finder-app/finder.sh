#!/bin/sh
# echo "Enter File Directory to be searched & string to be searched"
# echo "$#"
a=2 
if [ $# -ne $a ]; then
    echo "Fail: Parameter count incorrect" 
    exit 1
fi


filesdir=$1
searchstr=$2

# echo $filesdir
# echo $searchstr


if [ -d $filesdir ]; then
    # echo "$filesdir is a Vailid Dir"
    1>/dev/null 

else
    echo "$filesdir is not a Valid Dir"
    exit 1
fi

outputLineCtr=$(find "$filesdir" -type f | wc -l)

matchCtr=$(grep -lr "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $outputLineCtr and the number of matching lines are $matchCtr"

