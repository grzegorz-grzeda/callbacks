#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

$SCRIPT_DIR/packages/simple-documentation-library/document.py callbacks 1.0.1 "Simple callback library" source documentation