#!/bin/bash

docker-compose up -d
port=$(docker-compose port novnc 8080)
port=$(echo -n $port | tail -c 4)

echo Opening novnc at http://localhost:${port}

xdg-open http://localhost:${port}/vnc.html &

echo Running sim..

docker exec quadruped-sim_drake_1 bash -c "cd /quadruped-sim/quadruped_sim/build ; ./QuadrupedSim"