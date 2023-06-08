cmake_minimum_required(VERSION 3.21)
project(CurrecyConv)

set(CMAKE_CXX_STANDARD 14)

add_executable(CurrecyConv CurrencyConv.cpp "CurrConvFunc.h")
set(CMAKE_EXE_LINKER_FLAGS "-static")