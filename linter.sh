#! /bin/bash

BASEDIR=$(dirname "$0")

pep8 $(find ${BASEDIR} -name \*.py)

