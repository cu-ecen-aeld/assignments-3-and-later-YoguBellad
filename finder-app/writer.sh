set -e
expectedparam=2
if [ $# -ne $expectedparam ] ; then 
    echo "Fail : Incorrect inputs"
    exit 1
fi

writefile=$1
writestr=$2

# if [ -f $writefile ] ; then
#     echo "Invalid Path"
# fi
mkdir -p "$(dirname "$writefile")" 

if [ -d "$(dirname "$writefile")"  ]; then
    touch "$writefile"
    echo "$writestr" > "$writefile"
else
    echo "$writefile is not a Valid Path"
    exit 1
fi


