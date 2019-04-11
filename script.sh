#! /bin/bash
g++ main.cpp data.cpp edge.cpp node.cpp -g
echo "executing now"
./a.out $1
