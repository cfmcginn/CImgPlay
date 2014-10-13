#!/bin/bash                                                                           
if [ $# -ne 0 ]
then
  echo "Usage: ./pmakeDiJetIniSkim.sh"
  exit 1
fi

now="imageJob_$(date +"%m_%d_%Y__%H_%M_%S")"
mkdir $now

NAME="testProcess.cpp"
g++ $NAME -Werror -Wall -O2 -o "${NAME/%.cpp/}.exe" -I/usr/X11R6/include -L/usr/X11R6/lib -lX11

mv *.exe $now
cp testPhoto.jpg $now
