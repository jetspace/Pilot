build.sh
if [ "$?" != "0" ]
then
exit 2
fi

python2 src/main.py -t "current time in London?"
if [ "$?" != "0" ]
then
exit 2
fi

python2 src/main.py -t "weather in new York?"
if [ "$?" != "0" ]
then
exit 2
fi

python2 src/main.py -t "is it night in Sydney?"
if [ "$?" != "0" ]
then
exit 2
fi
