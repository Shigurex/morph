#!/bin/bash

cat *.csv | cut -d "," -f1 | fold -w 1 | sort | uniq > word.def