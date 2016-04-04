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

rm -rf ${OUT}
echo "
/**
 * Author: Andrei Maximov
 *
 * This is a concatenated version of the original source code which can be
 * found on my GitHub.
 *
 * https://github.com/andreimaximov/quora-typeahead-search
 */
" > ${OUT}
cat ${FILES} >> ${OUT}
sed -i "" "/#include[[:space:]]*\".*\.h\"/d" ${OUT}
