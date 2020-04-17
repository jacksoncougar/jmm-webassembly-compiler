#!/bin/bash

scp $1 jackson.wiebe1@linux.cpsc.ucalgary.ca:~
(
ssh -t -t -C  jackson.wiebe1@linux.cpsc.ucalgary.ca << DONTBEAHERO
sleep 5s && kill -9 -1 &
~aycock/411/bin/wat2wasm ${1%.*}.wat
~aycock/411/bin/wasm-interp --411 ${1%.*}.wasm
exit
DONTBEAHERO
) | tee console.txt