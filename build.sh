#!/bin/sh

set -xe

GCC=gcc
CFLAGS="-Wall -Wextra"

$GCC $CFLAGS -o main main.c