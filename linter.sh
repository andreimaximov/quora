#! /bin/bash

BASEDIR=$(dirname "$0")

cpplint $(find ${BASEDIR} -name \*.h -or -name \*.cpp)
