#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Please specify an output file"
    exit 1
fi

BASEDIR=$(dirname "$0")
SRC="${BASEDIR}/src"
OUT="${BASEDIR}/$1"

FILES="${SRC}/split.hpp ${SRC}/split.cpp"
FILES="${FILES} ${SRC}/intersection.hpp"
FILES="${FILES} ${SRC}/item.hpp ${SRC}/item.cpp"
FILES="${FILES} ${SRC}/query.hpp ${SRC}/query.cpp"
FILES="${FILES} ${SRC}/trie.hpp"
FILES="${FILES} ${SRC}/typeahead.hpp ${SRC}/typeahead.cpp"
FILES="${FILES} ${SRC}/query-parser.hpp ${SRC}/query-parser.cpp"
FILES="${FILES} ${SRC}/controller.hpp ${SRC}/controller.cpp"
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
sed -i "" "/#include[[:space:]]*\".*\.hpp\"/d" ${OUT}
