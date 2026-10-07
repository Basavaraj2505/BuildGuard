#!/bin/bash

set -e

echo "================================="
echo "      BuildGuard Local CI"
echo "================================="

echo
echo "[1/4] Building project..."
./scripts/build.sh

echo
echo "[2/4] Running tests..."
ctest --test-dir build --output-on-failure

echo
echo "[3/4] Scanning project..."
./build/buildguard scan .

echo
echo "[4/4] Generating report..."
./build/buildguard report .

echo
echo "================================="
echo "       LOCAL CI PASSED"
echo "================================="
