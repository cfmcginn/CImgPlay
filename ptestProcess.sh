#!/bin/bash                                                                           

if [ $# -ne 1 ]
then
  echo "Usage: ./pmakeDiJetIniSkim.sh <inFileName>"
  return
fi

now="imageJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now

NAME="testProcess.cpp"
g++ $NAME -Werror -Wall -O2 -o "${NAME/%.cpp/}.exe" -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -I/Users/cfmcginn/CPPLibraries

mv *.exe $now
cp $1 $now
