#!/bin/bash

echo "${red}"
echo '    ____  ____  _   ___ ______   ____  ___    _   ____________
   / __ \/ __ \/ | / ( )_  __/  / __ \/   |  / | / /  _/ ____/
  / / / / / / /  |/ /|/ / /    / /_/ / /| | /  |/ // // /     
 / /_/ / /_/ / /|  /   / /    / ____/ ___ |/ /|  // // /___   
/_____/\____/_/ |_/   /_/    /_/   /_/  |_/_/ |_/___/\____/   
                                                              
';

docker-compose up -d
port=$(docker-compose port novnc 8080)
port=$(echo -n $port | tail -c 4)

echo Opening novnc at http://localhost:${port}

xdg-open http://localhost:${port}/vnc.html &

echo Building application..

docker exec quadruped-sim_drake_1 bash -c "cd /quadruped-sim/quadruped_sim ; rm -r build ; mkdir build && cd build ; cmake .. ; cmake --build . ; ./QuadrupedSim"