#!/bin/bash
exec 3<> /dev/tcp/localhost/1697
for i in {1..7}
do
    read line;
    echo ${line};
done <&3

for i in {1..5}
do
    read line <&3;
    echo "hell";
    echo ${line} ;
    read sol ;
    echo ${sol} >&3;
    read res <&3;
    echo ${res} ;
done
read res <&3;
echo ${res} ;
read res <&3;
echo ${res} ;
read res <&3;
echo ${res} ;


