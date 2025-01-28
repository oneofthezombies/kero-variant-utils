#!/usr/bin/env bash

set -ex

# Check C++
clang --version
clang++ --version
clang-format --version
lldb --version
[[ "$(which lld)" == "/opt/llvm/bin/lld" ]] || exit 1
cmake --version
ctest --version
ninja --version

# Check JavaScript
volta --version
node --version
npm --version
gitmoji --version
tsx --version
