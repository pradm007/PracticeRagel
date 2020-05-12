# PracticeRagel (tQRE)

Practice repository for ragel using C and graphviz for visualization.

# Command

## Ragel build
ragel -C sample.rl -o sample.cpp

## Ragel graph vizualizer generation
- ragel -V sample.rl > sample.gv 
- dot -Tpng sample.gv -o sample.png
- display sample.png

## Shared library generation
- gcc  -g -Wall -Wextra -ldl -o a a.c (For C)
- gcc -fpic -w -g -shared -o a.so a.c -ldl

## Linking and loading .SO file
- g++ -w mainFile.cpp -ldl -o mainFile
Add -fpermissive to convert errors to warning. Use with caution.

## For Debugging purpose
- g++ -w mainFile.cpp -ldl -o mainFile && ./mainFile | less


## Experimental Notes Section
Possible Expressions

1. <0>[0]M[0,4]<2>[0]
2. <0.1>[0,10]M[0,4]<2.3>[0,4]
3. <0.1.2>[0,10,16]M[0,4]<2.3.4>[0,4,6]
4. (<0.1>)+[0,10]M[0,4](<2.3>)+[0,4]

Hard Expressions (for TRE in tQRE)
1. <0.<1.<2+.3>[0,20] >[0,10] >[0,5] (which resolves to 0(1(2+3)))
2. <0.<1.2+>+[0,20] >[0,10] >[0,5] (which resolves to 0(12+)+)

3. Inner-Nesting: Nesting out TRE in tQRE with time scope
(<2.(<0.1>)+[0,10]>)+[0,9]

It is not clear for outer timed scope, which time-entry for nested region should be picked. 
Ideally we can solve such complex expressions but with inclusion of QRE, the overall tQRE becomes too complex as a whole to track-debug-maintain.


# Working Original Code

This directory has the actual working code unlike the root direction, try 1, try 2 and others which are created for experimental attempts.

# Command

ragel -C ragelAttempt1.rl -o build/ragelAttemp1.cpp && g++ -D DEBUG=0 -D MINIMAL=1 -w build/ragelAttemp1.cpp -o build/ragelAttemp1

## Using synthetic trace file with redirection

cat ../Benchmark/Synthetic/trace1.txt | ./build/ragelAttemp1
