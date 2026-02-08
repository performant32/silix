#!/bin/bash
if [ -z $1 ]; then
    echo "Invalid output device \"$1\""
    exit 2
fi
if [ -z $2 ]; then
    echo "Invalid output device \"$2\""
    exit 1
fi
SCRIPT_DIR="$(dirname -- "$(readlink -f -- "$0")")"
dd if="$SCRIPT_DIR/../bin/$1/silix.iso" of=$2
