FROM dockcross/linux-armv6

ENV DEFAULT_DOCKCROSS_IMAGE linux-armv7-image
ENV TARGET_ARCHITECTURE=linux-armv7
ENV ON_DOCKER=true
ENV PKG_CONFIG_PATH=/usr/lib/arm-linux-gnueabihf/pkgconfig/:/usr/share/pkgconfig
ENV TOOLCHAIN_FILE=/usr/arm-linux-gnueabihf/Toolchain.cmake

RUN dpkg --add-architecture armhf
RUN apt-get update
RUN apt-get install -y apt-utils libcurl4-openssl-dev:armhf libgtk-3-dev:armhf libpango1.0-dev:armhf libatk1.0-dev:armhf libgdk-pixbuf2.0-dev:armhf libxi-dev:armhf libepoxy-dev:armhf libatk-bridge2.0-dev:armhf

