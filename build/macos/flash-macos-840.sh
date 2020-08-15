#!/bin/bash

adafruit-nrfutil --verbose dfu serial -pkg ../../output/$1 -b 115200 -p $2
