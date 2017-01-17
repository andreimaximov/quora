#! /bin/bash

BASEDIR=$(dirname "$0")

cpplint --extensions=hpp,cpp --recursive ${BASEDIR}/src ${BASEDIR}/include
