# PracticeRagel

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