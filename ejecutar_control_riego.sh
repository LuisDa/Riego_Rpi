#!/bin/bash

export LD_LIBRARY_PATH=./libcomms/:$LD_LIBRARY_PATH:.
./control_riego_rpi
