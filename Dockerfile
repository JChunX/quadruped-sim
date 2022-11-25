FROM robotlocomotion/drake:latest

SHELL ["/bin/bash", "-c"]
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update --fix-missing

RUN apt install -y software-properties-common wget curl gpg gcc git cmake g++ make xorg-dev libglfw3 libglfw3-dev
RUN apt install -y --no-install-recommends libssl-dev libmodule-install-perl libboost-all-dev libopenblas-dev
RUN apt install -y locate nano

RUN git clone https://github.com/deepmind/mujoco
WORKDIR /mujoco/
RUN mkdir build
WORKDIR /mujoco/build/
RUN cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
RUN cmake --build .
RUN cmake --install .
