#!/bin/bash

cd ~/Work/Games/ActionRPG
lcov --capture --directory ./build/test/ -b ./src/ --output-file ./build/test/coverage.info
lcov --remove ./build/test/coverage.info "/usr*" --output-file ./build/test/coverage.info
lcov --remove ./build/test/coverage.info "deps*" --output-file ./build/test/coverage.info
lcov --remove ./build/test/coverage.info "test*" --output-file ./build/test/coverage.info
lcov --remove ./build/test/coverage.info "shader*" --output-file ./build/test/coverage.info
lcov --remove ./build/test/coverage.info "messaging/concrete*" --output-file ./build/test/coverage.info
lcov --remove ./build/test/coverage.info "component/*" --output-file ./build/test/coverage.info

genhtml ./build/test/coverage.info --output-directory ./build/test/coverage &&
firefox ./build/test/coverage/index.html
