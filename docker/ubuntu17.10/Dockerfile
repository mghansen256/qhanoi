FROM ubuntu:17.10

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update

# first configure apt-get to use apt-cacher-ng if running on the host
# add --build-arg USEAPTCACHER=no to suppress looking for apt-cacher-ng
ARG USEAPTCACHER=yes
COPY docker/install-apt-cacher-ng-detector.sh /usr/local/bin
RUN chmod +x /usr/local/bin/install-apt-cacher-ng-detector.sh
RUN /usr/local/bin/install-apt-cacher-ng-detector.sh $USEAPTCACHER

# install eatmydata to speed up the installation process
RUN apt-get install -y eatmydata

# install build-tools and dependencies
RUN eatmydata apt-get -y install git cmake qt4-dev-tools qt4-qmake libqtcore4 g++ ninja-build

# for later X11 access
ENV QT_X11_NO_MITSHM=1

# create source and build directories
RUN mkdir -pv /src/qhanoi && mkdir -pv /build/qhanoi-ninja

# Import the repository into the image
# Requires start of the docker command from the root of the repository!
# docker build -t qhanoi -f docker/ubuntu17.10/Dockerfile .
# This import is done as late as possible, because every step after ADD
# is re-run by docker if the added directory was changed since the last
# run!
ADD . /src/qhanoi

# Build from source
# add --build-arg DOBUILD=no to avoid building
ARG DOBUILD=yes
# Note: default shell in docker is "sh", not "bash". In "sh", the comparison
#       done with "=" instead of "=="!
RUN if [ "$DOBUILD" = "yes" ] ; then \
    cd /build/qhanoi-ninja && cmake -G Ninja /src/qhanoi && ninja \
    ; fi

CMD bash
