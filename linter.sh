#! /bin/bash

BASEDIR=$(dirname "$0")

cpplint $(find ${BASEDIR} -name \*.hpp -or -name \*.cpp)
