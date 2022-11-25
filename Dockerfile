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

RUN ln -s /usr/bin/cmake /usr/local/bin/cmake

RUN git clone https://github.com/lcm-proj/lcm
WORKDIR /lcm/
RUN mkdir build
WORKDIR /lcm/build/
RUN cmake ..
RUN make
RUN make install