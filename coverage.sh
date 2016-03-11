#!/bin/bash

lcov --capture --directory ../build/test/ -b ./ --output-file ../build/test/coverage.info &&
genhtml ../build/test/coverage.info --output-directory ../build/test/coverage &&
firefox ../build/test/coverage/index.html
