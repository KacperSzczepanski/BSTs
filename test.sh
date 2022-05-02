#!/bin/bash

if [[ $# != 2 ]]; then
echo "Usage: $0 <program> <directory of tests>";
exit 1;
fi;

PROG=$1
DIR=$2

for f in $DIR/*.in; do
valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -q ./forests <$f >/dev/null 2>/dev/null;
if [ "$?" -eq "0" ]
then echo "Memory OK";
else echo "Problems with memory";
fi;
$PROG <$f >$DIR/ks418474.out 2>$DIR/ks418474.err;
DIFFSTD=$(diff $DIR/ks418474.out ${f%in}out);
DIFFERR=$(diff $DIR/ks418474.err ${f%in}err);
test=${f%.in};
test=${test#$DIR/};
if [ "$DIFFSTD" = "" ] && [ "$DIFFERR" = "" ]
then echo "Good answer on test '$test' with exitcode $?";
else echo "Bad answer on test '$test' with exitcode $?";
fi;
echo;
done;

rm $DIR/ks418474.out;
rm $DIR/ks418474.err;