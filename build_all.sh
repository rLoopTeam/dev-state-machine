#!/bin/bash

OUT="fcu_test"
echo "Building $OUT"
gcc src/*.c src/pod/*.c src/pod/BRAKES/*.c src/pod/BRAKES/BRAKE/*.c src/pod/COOLING/*.c src/pod/AUXPROP/*.c src/pod/ENGINES/*.c -o $OUT
