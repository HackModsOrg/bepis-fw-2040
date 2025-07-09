#!/bin/bash -eux
PICO_SDK_PATH=../3rdparty/pico-sdk cmake -DPICO_BOARD=bepis -DCMAKE_BUILD_TYPE=Debug ..; make
