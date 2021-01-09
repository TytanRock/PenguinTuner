FROM dockcross/linux-x64

ENV DEFAULT_DOCKCROSS_IMAGE linux-x64-image
ENV TARGET_ARCHITECTURE=linux-x64
ENV ON_DOCKER=true

RUN dpkg --add-architecture amd64
RUN apt-get update
RUN apt-get install -y make cmake libcurl4-openssl-dev:amd64 libgtk-3-dev:amd64

