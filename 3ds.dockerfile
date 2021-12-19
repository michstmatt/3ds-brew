FROM devkitpro/devkitarm

WORKDIR /3ds
COPY ./Makefile .
COPY ./source ./source

RUN make

ENV ADDRESS="ADDRESS"

CMD echo "Attempting to upload..." && timeout 10s $DEVKITPRO/tools/bin/3dslink --address $ADDRESS 3ds.3dsx
