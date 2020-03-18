# Working Original Code

This directory has the actual working code unlike the root direction, try 1, try 2 and others which are created for experimental attempts.

# Command

ragel -C ragelAttempt1.rl -o build/ragelAttemp1.cpp && g++ -std=c++17 -fopenmp -Ofast -D DEBUG=0 -D MINIMAL=1 -D FILEINPUT=1 -D MINIMAL_2=1 -D DISPLAY_MAP=0 -w build/ragelAttemp1.cpp -o build/ragelAttemp1

## Using synthetic trace file with redirection

cat ../Benchmark/Synthetic/trace1.txt | ./build/ragelAttemp1
