# COSC3500-parallel
A parallel hypercube tic-tac-toe engine using MCTS

This is the OpenMP branch.

COSC3500 Major Project Final

Compilation instructions:
I am using CMake to build my project. The version of CMake on getafix is new enough to be able to build my project, but if not, an installation script cmake.sh is provided.

1. Start in directory COSC3500-parallel
2. ```module load gnu cmake```
3. ```mkdir cmake-build```
4. ```cd cmake-build```
5. CMake never seems to detect the module loaded version of gcc. We have to manually set it using the following: ```cmake -D CMAKE_CXX_COMPILER=/opt/gnu/gcc/bin/g++ -D CMAKE_C_COMPILER=/opt/gnu/gcc/bin/gcc ../```
6. Ensure the CMake output has identified both the C and CXX compiler as GNU 7.2.0. If it hasn't, repeat the previous command. It usually works when done twice in a row.
7. ```cmake --build .```
8. We should now be able to run our program. ```./parallel``` or ```./tests 3 3 10 1 4```. See tests.cpp for an explanation of tests' commandline arguments.
