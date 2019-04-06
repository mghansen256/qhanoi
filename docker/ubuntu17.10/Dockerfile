FROM ubuntu:17.10

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update

# first configure apt-get to use apt-cacher-ng if running on the host
COPY docker/install-apt-cacher-ng-detector.sh /usr/local/bin
RUN chmod +x /usr/local/bin/install-apt-cacher-ng-detector.sh
RUN /usr/local/bin/install-apt-cacher-ng-detector.sh

# install eatmydata to speed up the installation process
RUN apt-get install -y eatmydata

# install build-tools and dependencies
RUN eatmydata apt-get -y install git cmake qt4-dev-tools qt4-qmake libqtcore4 g++ ninja-build

# Import the repository into the image
# Requires start of the docker command from the root of the repository!
# docker build -t qhanoi -f docker/ubuntu17.10/Dockerfile .
RUN mkdir -pv /src/qhanoi
ADD . /src/qhanoi

# for later X11 access
ENV QT_X11_NO_MITSHM=1

# create build directory and start the build
RUN mkdir -pv /build/qhanoi-ninja && cd /build/qhanoi-ninja && cmake -G Ninja /src/qhanoi && ninja


CMD bash
