#!/bin/bash

SRC="main.cpp"
BASE_NAME="main"

OPT_FLAGS=("-O0" "-O1" "-O2" "-O3" "-Os")

for OPT in "${OPT_FLAGS[@]}"; do
    EXEC_NAME="${BASE_NAME}_${OPT}"
    DIR_NAME="profile_${OPT}"
    mkdir -p "$DIR_NAME"

    g++ -pg -g $OPT "$SRC" -o "${DIR_NAME}/${EXEC_NAME}"

    (cd "$DIR_NAME" && ./"$EXEC_NAME")

    (cd "$DIR_NAME" && \
        gprof "$EXEC_NAME" gmon.out > "analysis_${OPT}.txt" && \
        gprof "$EXEC_NAME" | python3 ../gprof2dot.py -n0 -e0 | dot -Tpng -o "callgraph_${OPT}.png")
done

echo "Графы и отчёты сохранены в поддиректориях profile_*/"