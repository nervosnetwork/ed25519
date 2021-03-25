#!/bin/bash
set -e
cd "$(dirname "${BASH_SOURCE[0]}")"
mkdir -p build.simulator
cd build.simulator
cmake -DCMAKE_C_COMPILER=clang ..
make all

function test_one() {
  echo "test vector from $1"
  FN=$1
  cat $FN | while read line || [[ -n $line ]];
  do
     ./portable_ed25519 -t ${line//:/ 0x}
  done
}

test_one ../tests/TESTVECTORS
test_one ../tests/polkadot.txt

echo "if no output from stdout, it means success!"
