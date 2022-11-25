#!/bin/bash
docker build . -t jchun/drake-dev:latest
docker-compose up -d

echo Building sim..

docker exec quadruped-sim_drake_1 bash -c "cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/quadruped-sim/quadruped_sim -B/quadruped-sim/build -G 'Unix Makefiles' ; cmake --build /quadruped-sim/build --config Debug --target all -j 6 --"