#! /bin/bash

BASEDIR=$(dirname "$0")

cpplint --root=related-questions \
	--extensions=hpp,cpp \
	--recursive ${BASEDIR}

