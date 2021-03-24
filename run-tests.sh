#!/bin/bash
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
mkdir -p build.simulator
cd build.simulator
cmake -DCMAKE_C_COMPILER=clang ..
make all

cat ../tests/TESTVECTORS | while read line || [[ -n $line ]];
do
   ./portable_ed25519 -t ${line//:/ 0x}
done

echo "if no output from stdout, it means success!"
