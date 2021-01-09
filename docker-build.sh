#!/bin/bash

docker build -t $1-image dockerfiles/$1/
docker run $1-image > $1
chmod +x $1
./$1 $2
rm $1

