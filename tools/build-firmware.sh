#!/bin/sh

set -e    # Exit on error

git submodule update --init
cd Code/lib/pico-sdk/
git submodule update 
export PICO_SDK_PATH=$PWD
cd ../..
mkdir -p build
cp ./lib/pico-sdk/external/pico_sdk_import.cmake .
cd build
cmake ..
make -j $(($(nproc) * 2))

while getopts 'l' flag; do
  case "${flag}" in (l) 
      echo "Loading firmware <$(pwd)/src/firmware/firmware.bin> to Pico"
      sudo picotool load $(pwd)/src/firmware/firmware.bin
      ;;
  esac
done