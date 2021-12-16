FROM frolvlad/alpine-gxx

COPY . /app
RUN apk update
RUN apk add ncurses-lib \
    ncurses-dev \
    bash \
    bash-doc \
    bash-completition \
    libstdc++ \
    g++ \
    make

WORKDIR /app

ENTRYPOINT /bin/bash