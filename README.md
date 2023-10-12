# callbacks
[![CMake](https://github.com/grzegorz-grzeda/callbacks/actions/workflows/cmake.yml/badge.svg)](https://github.com/grzegorz-grzeda/callbacks/actions/workflows/cmake.yml)

Simple C library for handling callbacks

This is a [G2EPM](https://github.com/grzegorz-grzeda/g2epm) library.

## Initialize
Download dependencies by running `g2epm download` in the project root.

## Run tests
Just run `./test.sh`.

## How to compile and link it?

Just include this directory in your CMake project.

Example `CMakeLists.txt` content:
```
...

add_subdirectory(<PATH TO CONTAINERS LIBRARY>)

target_link_libraries(${PROJECT_NAME} PRIVATE callbacks)

...
```

# Copyright
This library was written by G2Labs Grzegorz Grzęda, and is distributed under MIT Licence. Check the `LICENSE` file for
more details.