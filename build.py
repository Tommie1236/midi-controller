#!/usr/bin/env python3

import os
import subprocess
import sys
import argparse


def main():
    
    parser = argparse.ArgumentParser(description='Build and load the firmware for a rp2040 board.')
    parser.add_argument('-l', '--load', nargs='?', type=str, help='load the specified firmware file, or show a menu to choose one.')

    args = parser.parse_args()

    # build the project:

    # git submodule update --init
    # cd Code/lib/pico-sdk/
    # git submodule update 
    # export PICO_SDK_PATH=$PWD
    # cd ../..
    # mkdir -p build
    # cp ./lib/pico-sdk/external/pico_sdk_import.cmake .
    # cd build
    # cmake ..
    # make -j $(($(nproc) * 2))
    subprocess.run(["git", "submodule", "update", "--init"], check=True)
    os.chdir("Code/lib/pico-sdk")
    subprocess.run(["git", "submodule", "update"], check=True)
    os.environ["PICO_SDK_PATH"] = os.getcwd()
    os.chdir('../..')
    os.makedirs('build', exist_ok=True)
    subprocess.run(['cp', './lib/pico-sdk/external/pico_sdk_import.cmake', '.'], check=True)
    os.chdir('build')
    subprocess.run(['cmake', '..'], check=True)
    subprocess.run(['make', '-j', str(os.cpu_count() * 2)], check=True)

    
    if args.load is not None:
        if args.load is None:
            # No argument provided, show menu to choose a binary
            print("Available binaries:")
            binaries = [os.path.join(root, file) for root, _, files in os.walk('build/src') for file in files if file.endswith('.bin') and ('firmware' in root or 'fader-wing' in root)]
            
            if not binaries:
                print("No binaries found.")
                sys.exit(1)
            
            for i, bin_file in enumerate(binaries, start=1):
                print(f"{i}) {bin_file}")
            
            try:
                index = int(input("Select a binary by index: "))
                if index < 1 or index >= len(binaries):
                    raise ValueError
                binary = binaries[index - 1]
            except (ValueError, IndexError):
                print("Invalid index selected.")
                sys.exit(1)
            
        else:
            # Load the specified file
            if os.path.isfile(args.load):
                binary = args.load
            else:
                print(f"File not found: {args.load}")
                sys.exit(1)

        # Load the selected or specified binary
        print(f"Loading firmware <{binary}> to Pico")
        subprocess.run(['sudo', 'picotool', 'load', binary], check=True)







if __name__ == '__main__':
    main()