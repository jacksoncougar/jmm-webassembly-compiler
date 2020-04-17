#!/bin/bash

scp $1 jackson.wiebe1@linux.cpsc.ucalgary.ca:~
(
ssh -t -t -C  jackson.wiebe1@linux.cpsc.ucalgary.ca << DONTBEAHERO
~aycock/411/bin/wat2wasm result.wat
~aycock/411/bin/wasm-interp --411 result.wasm
exit
DONTBEAHERO
) | tee console.txt