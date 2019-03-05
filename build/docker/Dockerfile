FROM guidolib:1.6.7

RUN apt-get update -qq
RUN apt-get install -y libmicrohttpd-dev libpulse-dev
RUN apt-get install -y libqt5svg5-dev libqt5websockets5-dev libqt5sensors5-dev qtmultimedia5-dev qtdeclarative5-dev

WORKDIR /grame
RUN git clone --single-branch -b dev --depth 1 https://github.com/grame-cncm/inscore.git
WORKDIR /grame/inscore/build
RUN git pull
RUN make -j 4

