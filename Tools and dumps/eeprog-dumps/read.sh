#!/bin/bash
./eeprog -fx -o $1 /dev/i2c-1 0x52 -16 -r 0x00:0x10000
