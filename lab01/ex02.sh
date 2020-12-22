#!/bin/bash

file=./My-exercise-1/source/edit.txt
folder=`pwd`

rm -f $file
touch $file

for i in {1..5}
do
   echo "This is line number $i" >> $file
done

cp $file ./My-exercise-1/test/alfa/edit.txt		# relative path
cp $file $folder/My-exercise-1/test/beta/edit.txt	# absolute path
