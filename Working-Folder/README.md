# Working Original Code

This directory has the actual working code unlike the root direction, try 1, try 2 and others which are created for experimental attempts.

# Command

ragel -C ragelAttempt1.rl -o build/ragelAttemp1.cpp && g++ -D DEBUG=0 -D MINIMAL=1 -w build/ragelAttemp1.cpp -o build/ragelAttemp1

## Using synthetic trace file with redirection

cat ../Benchmark/Synthetic/trace1.txt | ./build/ragelAttemp1
