#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Please specify an output file"
    exit 1
fi

BASEDIR=$(dirname "$0")
SRC="${BASEDIR}/src"
INC="${BASEDIR}/include"
OUT="${BASEDIR}/$1"

FILEs=""
FILES="${FILES} ${INC}/actors.hpp ${SRC}/actors.cpp"
FILES="${FILES} ${INC}/trie.hpp   ${SRC}/trie.cpp"
FILES="${FILES} ${SRC}/main.cpp"

rm -rf ${OUT}
echo "
/**
 * Author: Andrei Maximov
 *
 * This is a concatenated version of the original source code which can be
 * found on my GitHub.
 *
 * https://github.com/andreimaximov/quora/ontology
 */
" > ${OUT}
cat ${FILES} >> ${OUT}
sed -i "" "/#include[[:space:]]*\".*\.hpp\"/d" ${OUT}
