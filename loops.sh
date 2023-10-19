#!/bin/bash

if [[ $# != 2 ]]; then
	echo "args"
	exit 1
fi

N=$1
Text=$2

for ((i=1; i<=N; ++i)); do
	filename="file_$i.txt"
	echo "$Text $i" > "$filename"
done
