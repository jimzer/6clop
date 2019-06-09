#!/usr/bin/env bash

while inotifywait -e modify -r ../src ../test; do
	clear && printf '\e[3J'i; make -C ../build -j4 && valgrind --leak-check=yes ../build/test/unit_tests
done

