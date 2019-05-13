cmake_minimum_required(VERSION 3.10)
project(OJOnly)

set(CMAKE_CXX_STANDARD 11)
ADD_DEFINITIONS(-DLOCALLL)

add_executable(OJOnly main.cpp Utils.h BigInt.h FenwickTree.h UnionFind.h KMP.h RMQ.h IntHashMap.h)