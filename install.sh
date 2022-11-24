#!/bin/bash

# clone drake if it doesn't exist
if [ ! -d drake ]; then
    git clonevgit@github.com:RobotLocomotion/drake.git
fi

# if there is conda, deactivate it
if [ -n "$CONDA_PREFIX" ]; then
    conda deactivate
fi

#bash drake/setup/mac/install_prereqs.sh

# curl if file doesn't exist
if [ ! -f drake-latest-focal.tar.gz ]; then
    curl -O https://drake-packages.csail.mit.edu/drake/nightly/drake-latest-focal.tar.gz
fi

sudo tar -xvzf drake-latest-focal.tar.gz -C /opt
rm drake-latest-focal.tar.gz

cd quadruped_sim
sudo rm -r build
mkdir build && cd build
cmake ..
cmake --build .
make