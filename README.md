# COSC3500-serial
A serial checkers engine using MCTS

COSC3500 Major Project Milestone 1

Compilation instructions:
I am using cmake to build my project, however unfortunately the version of cmake on moss is outdated and does not support c++11 onwards.
Hence I have included an install script for cmake.
1. Start in directory COSC3500-serial/cmake_install
2. ```./cmake.sh```, hit enter until prompted for y/n. Hit y until finished.
3. ```cd ../```, we should now be in the directory COSC3500-serial
4. ```mkdir cmake-build```, our build goes here
5. ```cd cmake-build```
6. ```../cmake_install/cmake-3.18.2-Linux-x86_64/bin/cmake ../```
7. ```../cmake_install/cmake-3.18.2-Linux-x86_64/bin/cmake --build .```
8. We should have made our executable. Run with ```./serial```