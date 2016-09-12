#! /bin/bash

BASEDIR=$(dirname "$0")

cpplint --root=typeahead-search \
	--extensions=hpp,cpp \
	--recursive ${BASEDIR}

