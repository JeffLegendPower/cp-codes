#!/bin/bash

# problem="nile"
# grader_name="grader"

problem="/Users/ishaangoyal/Desktop/USACO:Codeforces/oj.uz/Nile (IOI24_nile)/nile/cpp/nile"
grader_name="/Users/ishaangoyal/Desktop/USACO:Codeforces/oj.uz/Nile (IOI24_nile)/nile/cpp/grader"

g++ -std=gnu++17 -Wall -O2 -pipe -static -g -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"