FROM ubuntu:16.10

# first configure apt-get to use apt-cacher-ng if running on the host:
# http://askubuntu.com/questions/53443/how-do-i-ignore-a-proxy-if-not-available
# https://gist.github.com/wassname/6e97c2165d9ffe13b270
# configure apt to not install reccomendations
ENV DEBIAN_FRONTEND noninteractive

# TODO: turning off recommends creates a lot of work to find all packages
# for "normal" operation. For git, ca-certificates is kind of required...
#RUN echo 'APT::Install-Recommends 0;' >> /etc/apt/apt.conf.d/01norecommends \
# && echo 'APT::Install-Suggests 0;' >> /etc/apt/apt.conf.d/01norecommends

RUN apt-get update \
 && apt-get install -y netcat iproute2

# This uses the apt proxy only if present. It checks on port 3142 of the host/gateway, and returns DIRECT for no proxy,
# or the proxy address if it's detected. This uses an undocumented feature of apt-get.
# Ref: http://askubuntu.com/questions/53443/how-do-i-ignore-a-proxy-if-not-available
RUN export HOST_IP=$(ip route| awk '/^default/ {print $3}')\
 && echo "#!/bin/bash" > /usr/local/bin/apt-ng-host-discover \
 && echo "if nc -w1 -z $HOST_IP 3142; then printf http://$HOST_IP:3142; else printf DIRECT; fi" >> /usr/local/bin/apt-ng-host-discover \
 && chmod +x /usr/local/bin/apt-ng-host-discover \
 && echo 'Acquire::http::Proxy-Auto-Detect "/usr/local/bin/apt-ng-host-discover";' > /etc/apt/apt.conf.d/30proxy \
 && echo "Host for apt-cacher-ng: " $(/usr/local/bin/apt-ng-host-discover)

# install eatmydata to speed up the installation process
RUN apt-get install -y eatmydata

# install build-tools and dependencies
RUN eatmydata apt-get -y install git cmake qt4-dev-tools qt4-qmake libqtcore4 g++ ninja-build

# check out source code
RUN mkdir -pv /src && cd /src && git clone https://github.com/mghansen256/qhanoi

# for later X11 access
ENV QT_X11_NO_MITSHM=1

# create build directory and start the build
RUN mkdir -pv /build/qhanoi-ninja && cd /build/qhanoi-ninja && cmake -G Ninja /src/qhanoi && ninja

CMD bash
