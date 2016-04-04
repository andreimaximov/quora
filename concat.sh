#!/bin/bash

BASEDIR=$(dirname "$0")
SRC="${BASEDIR}/src"
OUT="${BASEDIR}/$1"

FILES="${SRC}/split.h ${SRC}/split.cpp"
FILES="${FILES} ${SRC}/item.h ${SRC}/item.cpp"
FILES="${FILES} ${SRC}/query.h"
FILES="${FILES} ${SRC}/trie.h"
FILES="${FILES} ${SRC}/trie-map.h"
FILES="${FILES} ${SRC}/memory-service.h ${SRC}/memory-service.cpp"
FILES="${FILES} ${SRC}/query-parser.h ${SRC}/query-parser.cpp"
FILES="${FILES} ${SRC}/controller.h ${SRC}/controller.cpp"
FILES="${FILES} ${SRC}/main.cpp"

cat ${FILES} > ${OUT}
sed -i "" "/#include[[:space:]]*\".*\.h\"/d" ${OUT}
