FROM dockcross/linux-armv6

ENV DEFAULT_DOCKCROSS_IMAGE linux-armv6-image
ENV TARGET_ARCHITECTURE=linux-armv6
ENV ON_DOCKER=true
ENV PKG_CONFIG_PATH=/usr/lib/arm-linux-gnueabihf/pkgconfig/
ENV TOOLCHAIN_FILE=/usr/armv6-linux-gnueabihf/Toolchain.cmake

RUN dpkg --add-architecture armhf
RUN apt-get update
RUN apt-get install -y libcurl4-openssl-dev:armhf libgtk-3-dev:armhf
