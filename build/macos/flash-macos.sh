#!/bin/bash

nrfutil --verbose dfu serial -pkg ../../output/$1 -p $2 -b 115200
