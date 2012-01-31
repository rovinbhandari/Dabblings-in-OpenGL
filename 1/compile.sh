#!/bin/bash

sourcepath=$2
cc=$1

dirpath=$(dirname $sourcepath)
filename=$(basename $sourcepath)

command="$cc -Wall -g $sourcepath -o $dirpath/${filename%.*}.out -lGL -lglut -lGLU -lm -I/usr/X11R6/include -L/usr/X11R6/lib"

echo $command

$($command)
