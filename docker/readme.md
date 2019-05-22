Building qhanoi inside docker images
====================================

## Building under ubuntu
 # Build the image from the main directory of this repository,
 # because only then will the ADD commands in Dockerfile work correctly:

sudo docker build -t qhanoi -f docker/Dockerfile-ubuntu-17.10 .

 # open x-server for access from container (considered insecure AFAIK)
xhost +local:a

 # start the image in a container named qhanoi-1
sudo docker run -it -e DISPLAY=$DISPLAY -v /tmp/.X11-unix/:/tmp/.X11-unix --name qhanoi-1 qhanoi

 # to restart the image where you left off, note that you are stuck on the same display!
sudo docker start -i qhanoi-1
