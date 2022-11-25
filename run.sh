#!/bin/bash

docker-compose up -d
port=$(docker-compose port novnc 8080)
port=$(echo -n $port | tail -c 4)

echo Opening novnc at http://localhost:${port}

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    xdg-open http://localhost:${port}/vnc.html &
elif [[ "$OSTYPE" == "darwin"* ]]; then
    open http://localhost:${port}/vnc.html &
fi

echo Running sim..

docker exec quadruped-sim_drake_1 bash -c "cd /quadruped-sim/build ; ./QuadrupedSim"