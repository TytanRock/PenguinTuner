#!/bin/bash

timeout 10s xvfb-run -a PenguinTuner

if (($? == 124))
then
    echo "Test successful"
    exit 0
else
    echo "Test unsuccessful"
    exit 1
fi