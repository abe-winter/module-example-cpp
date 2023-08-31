#!/usr/bin/env bash
# run.sh -- entrypoint wrapper for the module

# bash safe mode
set -euo pipefail

cd $(dirname $0)
# get bundled .so files from this directory
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH-}:$PWD
exec ./module-example-cpp $@
