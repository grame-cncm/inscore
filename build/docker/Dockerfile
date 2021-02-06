FROM ubuntu:bionic

RUN apt-get update -qq
RUN apt-get install -y libmicrohttpd-dev libpulse-dev
RUN apt-get install -y libqt5svg5-dev libqt5websockets5-dev libqt5sensors5-dev qtmultimedia5-dev qtdeclarative5-dev
RUN apt-get install -y cmake git libcairo2-dev

WORKDIR /grame
RUN git clone --single-branch -b dev --depth 1 https://github.com/grame-cncm/inscore.git
WORKDIR /grame/inscore/build
RUN make modules -j 4
RUN mkdir inscoredir
RUN make inscore -j 4

