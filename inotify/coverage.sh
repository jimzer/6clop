#!/usr/bin/env bash

make -C ../build -j8
../build/test/unit_tests
lcov --directory ../build/src \
     --base-directory ../build \
     --gcov-tool ../inotify/llvm-gcov.sh \
     --capture -o ../build/cov.info
genhtml ../build/cov.info -o ../build/output
chromium $(realpath ../build/output/index.html)