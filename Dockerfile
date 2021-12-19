FROM frolvlad/alpine-gxx

COPY . /app
RUN apk update
RUN apk add ncurses-libs \
    ncurses-dev \
    bash \
    bash-doc \
    bash-completion \
    libstdc++ \
    g++ \
    make

WORKDIR /app

ENTRYPOINT /bin/bash