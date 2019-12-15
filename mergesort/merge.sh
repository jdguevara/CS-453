#!/bin/bash

# This is to help me run the effectiveness tests so I don't have to sit here waiting for each one to finish

x=1000000
y=1
for ((i=1; i<101; i++))
do
	elements=$(($x * $i))
	./mytests "$elements" "$y" "-f"
done
