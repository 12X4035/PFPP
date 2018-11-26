cmake_minimum_required(VERSION 3.0)

project(cppmod)

set(PYBIND11_CPP_STANDARD -std=c++11)
set(CMAKE_CXX_FLAGS "-Wall -O3")
set(CPLUS_INCLUDE_PATH "/Users/d/.pyenv/versions/miniconda3-latest/lib/python3.6/site-packages")
set(PYBIND11_PYTHON_VERSION 3.6)
find_package(pybind11 REQUIRED)

pybind11_add_module(backward SHARED backward.cpp)
#pybind11_add_module(backward_no_eps SHARED backward_no_eps.cpp) 
pybind11_add_module(forward SHARED forward.cpp) 
