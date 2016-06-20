#!/bin/bash

i="0"

./inc_dec i

while [ $i -lt 100 ]
do 
./inc_dec + m &
i=$[$i+1]
done

i="0"
while [ $i -lt 100 ]
do 
./inc_dec 0 m &
i=$[$i+1]
done

i="0"
while [ $i -lt 100 ]
do 
./inc_dec - m &
i=$[$i+1]
done

sleep 15s
./read_number
