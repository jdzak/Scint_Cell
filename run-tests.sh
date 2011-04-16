#!/bin/bash

############################################
# TEST RUNNER                              #
#                                          #
# You can run the test runner two ways     #
# 1. No arguments (All tests)              #
# 2. One argument (One test)               #
#                                          #
############################################
TEST_DIR="test/build"

make

if [ $? -eq 0 ] ; then
  if [ -n "$1"  ]; then
    exec $TEST_DIR/$1
  else
    for f in $TEST_DIR/*Test
    do
        echo "Running test - $f"
        exec $f
    done
  fi
fi