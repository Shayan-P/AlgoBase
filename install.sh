#!/bin/bash

# Get the current working directory
script_dir=$(dirname "$(realpath "$0")")
lib_dir="$script_dir/lib"

if [ ! -d "$lib_dir" ]; then
    echo "Error: $lib_dir directory not found."
else
    # Create a symbolic link from pwd/lib to /usr/include
    sudo ln -s "$lib_dir" /usr/include/AlgoBase
    # Add the current directory to PATH in .bashrc
    echo "export PATH=\$PATH:$script_dir" >> ~/.bashrc
    echo "installed successfully"
fi

# Reload the .bashrc file to apply changes
source ~/.bashrc
