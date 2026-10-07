#!/bin/bash

set -e

echo "================================="
echo "       BuildGuard Build"
echo "================================="

echo "[1/2] Configuring project..."

cmake -S . -B build -G Ninja

echo
echo "[2/2] Building project..."

cmake --build build

echo
echo "================================="
echo "       BUILD SUCCESS"
echo "================================="
