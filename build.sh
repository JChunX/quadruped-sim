#!/bin/bash
docker build .
docker-compose up -d

echo Building sim..

docker exec quadruped-sim_drake_1 bash -c "cd /quadruped-sim/quadruped_sim ; rm -r build ; mkdir build && cd build ; cmake .. ; cmake --build ."