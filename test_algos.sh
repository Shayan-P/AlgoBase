#!/bin/bash

script_dir=$(dirname "$(realpath "$0")")
directory="${script_dir}/tests"

cd $script_dir

if [ -d build-test ]; then
    rm -r build-test
fi

mkdir build-test
cd build-test

if [ -d "$directory" ]; then
    files_to_process=()

    if [[ -n "$1" ]]; then
        files_to_process+=("$directory/$1")
    else 
        files_to_process=("$directory"/*.cpp)
    fi

    for file in $files_to_process; do
        if [[ -f "$file" && "$file" == *.cpp ]]; then
            echo "running $file"
            $script_dir/run $file
        else
            echo $file invalid
        fi
    done
else
    echo "Error: Directory $directory does not exist."
fi
