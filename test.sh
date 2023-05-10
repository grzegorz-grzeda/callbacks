#!/bin/bash
BUILD_DIR=$(mktemp -d -t callbacks-build-XXXXXXXXXX)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

pushd $BUILD_DIR
cmake -GNinja $SCRIPT_DIR
cmake --build .
ctest . --verbose
popd
rm -rf $BUILD_DIR